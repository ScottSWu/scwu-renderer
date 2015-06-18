#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "Pineapple/Renderer/GLRenderer.hpp"
#include "Pineapple/Object3D.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Camera/PerspectiveCamera.hpp"
#include "Pineapple/Renderer.hpp"
#include "Pineapple/Renderer/GLShader.hpp"
#include "Pineapple/Shape/Mesh.hpp"

GLRenderer::GLRenderer() :
        Renderer() {
    init = false;
}

GLRenderer::~GLRenderer() {
    
}

bool _tmp_first = true;
void GLRenderer::render(float imageBuffer[], Scene * scene) {
    if (!init) {
        initGL();
    }
    
    Camera * camera = scene->getCamera();
    
    int width = camera->viewport.x;
    int height = camera->viewport.y;
    
    PerspectiveCamera * pcamera = dynamic_cast<PerspectiveCamera *>(camera);
    float fov = 45.f;
    if (pcamera != 0) {
        fov = pcamera->fov;
    }

    float ratio = (float) width / (float) height;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);
    
    // Compute uniforms
    glm::vec3 vViewport = glm::vec3(width, height, fov);
    glm::vec3 vCameraPosition = camera->position;
    glm::vec3 vCameraDirection = glm::normalize(camera->target - camera->position);
    glm::mat4 mProjection = camera->computeProjectionMatrix();
    glm::mat4 mView = camera->computeCameraMatrix();
    glm::mat4 mProjectionView = mProjection * mView;

    // Bind default shader
    GLShader defaultShader = shaders[0];
    defaultShader.bind();

    glUniform3fv(defaultShader.vViewportId, 1, &vViewport[0]);
    glUniform3fv(defaultShader.vCameraPositionId, 1, &vCameraPosition[0]);
    glUniform3fv(defaultShader.vCameraDirectionId, 1, &vCameraDirection[0]);
    glUniformMatrix4fv(defaultShader.mProjectionViewId, 1, GL_FALSE, &mProjectionView[0][0]);
    glUniformMatrix4fv(defaultShader.mProjectionId, 1, GL_FALSE, &mProjection[0][0]);
    glUniformMatrix4fv(defaultShader.mViewId, 1, GL_FALSE, &mView[0][0]);
    
    //printf("Loop\n");
    // Render default objects
    int lastShader = 0;
    for (int i = 0, l = defaultMeshes.size(); i < l; i++) {
        renderObject(defaultMeshes[i], lastShader, vViewport, vCameraPosition, vCameraDirection, mProjection, mView);
    }
    
    // Render scene objects
    std::vector<Object3d *> objects = scene->getObjects();
    for (int i = 0, l = objects.size(); i < l; i++) {
        renderObject(objects[i], lastShader, vViewport, vCameraPosition, vCameraDirection, mProjection, mView);
    }

    shaders[lastShader].unbind();
}

void GLRenderer::renderObject(Object3d * object, int & lastShader, glm::vec3 & vViewport, glm::vec3 & vCameraPosition,
        glm::vec3 & vCameraDirection, glm::mat4 & mProjection, glm::mat4 & mView) {
    // Check if object is a mesh
    Mesh * mesh = dynamic_cast<Mesh *>(object);
    if (mesh != 0) {
        // Make indexing space if necessary
        while (mesh->rendererIndex.size() <= rendererId) {
            mesh->rendererIndex.push_back(0);
        }
        // Check if the buffer has already been made, otherwise generate it
        if (mesh->rendererIndex[rendererId] == 0) {
            // This function does the same checks again
            generateBuffer(mesh);
        }

        // Render the buffer
        int bufferIndex = mesh->rendererIndex[rendererId];
        renderBuffer(buffers[bufferIndex], lastShader, vViewport, vCameraPosition, vCameraDirection, mProjection,
                mView);
    }

    for (int i = 0, l = object->children.size(); i < l; i++) {
        renderObject(object->children[i], lastShader, vViewport, vCameraPosition, vCameraDirection, mProjection, mView);
    }
}

void GLRenderer::renderBuffer(GLBuffer & buffer, int & lastShader, glm::vec3 & vViewport, glm::vec3 & vCameraPosition,
        glm::vec3 & vCameraDirection, glm::mat4 & mProjection, glm::mat4 & mView) {
    GLShader currentShader = shaders[lastShader];
    if (buffer.shaderIndex != lastShader) {
        // Bind new shader
        currentShader.unbind();
        currentShader = shaders[buffer.shaderIndex];
        currentShader.bind();

        glm::mat4 mProjectionView = mProjection * mView;
        glUniform3fv(currentShader.vViewportId, 1, &vViewport[0]);
        glUniform3fv(currentShader.vCameraPositionId, 1, &vCameraPosition[0]);
        glUniform3fv(currentShader.vCameraDirectionId, 1, &vCameraDirection[0]);
        glUniformMatrix4fv(currentShader.mProjectionViewId, 1, GL_FALSE, &mProjectionView[0][0]);
        glUniformMatrix4fv(currentShader.mProjectionId, 1, GL_FALSE, &mProjection[0][0]);
        glUniformMatrix4fv(currentShader.mViewId, 1, GL_FALSE, &mView[0][0]);

        lastShader = buffer.shaderIndex;
    }
    glm::mat4 mTransform;
    glm::mat4 mTransformIT;
    glUniformMatrix4fv(currentShader.mTransformId, 1, GL_FALSE, &mTransform[0][0]);
    glUniformMatrix4fv(currentShader.mTransformITId, 1, GL_FALSE, &mTransformIT[0][0]);

    buffer.bind(currentShader);
    buffer.render();
}

void GLRenderer::initGL() {
    // Background color
    glClearColor(0.f, 0.f, 0.5f, 1.f);
    glEnable(GL_DEPTH_TEST);
    
    // Shader program and uniforms
    GLShader defaultShader;
    defaultShader.load("./res/Diffuse.vert", "./res/Diffuse.frag");
    shaders.push_back(defaultShader);
    
    // Create buffers
    GLBuffer defaultBuffer;
    buffers.push_back(defaultBuffer);
    
    // ================ TEST ================
    // Basic grid
    Mesh * grid = new Mesh();

    for (int i = -4; i <= 4; i++) {
        grid->positions.push_back(glm::vec4(-4.f, 0.f, (float) i, 1.f));
        grid->normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid->positions.push_back(glm::vec4(4.f, 0.f, (float) i, 1.f));
        grid->normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid->positions.push_back(glm::vec4(4.f, 0.f, (float) i, 1.f));
        grid->normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid->positions.push_back(glm::vec4((float) i, 0.f, -4.f, 1.f));
        grid->normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid->positions.push_back(glm::vec4((float) i, 0.f, 4.f, 1.f));
        grid->normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid->positions.push_back(glm::vec4((float) i, 0.f, 4.f, 1.f));
        grid->normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid->vertexCount += 6;
    }

    grid->fillDefault();

    // Indices
    for (unsigned int i = 0; i < 9 * 2; i++) {
        grid->faces.push_back(glm::uvec3(3 * i + 0, 3 * i + 1, 3 * i + 2));
        grid->faceCount++;
    }

    grid->wireframe = true;
    grid->properties["vertex-shader"] = "./res/Line.vert";
    grid->properties["fragment-shader"] = "./res/Line.frag";

    generateBuffer(grid);
    defaultMeshes.push_back(grid);

    // Background
    Mesh * background = new Mesh();

    background->positions.push_back(glm::vec4(-1.f, -1.f, 1.f, 1.f));
    background->positions.push_back(glm::vec4(1.f, -1.f, 1.f, 1.f));
    background->positions.push_back(glm::vec4(1.f, 1.f, 1.f, 1.f));
    background->positions.push_back(glm::vec4(-1.f, 1.f, 1.f, 1.f));

    background->normals.push_back(glm::vec4(0.f, 0.f, 1.f, 0.f));
    background->normals.push_back(glm::vec4(0.f, 0.f, 1.f, 0.f));
    background->normals.push_back(glm::vec4(0.f, 0.f, 1.f, 0.f));
    background->normals.push_back(glm::vec4(0.f, 0.f, 1.f, 0.f));

    background->faces.push_back(glm::uvec3(0, 1, 2));
    background->faces.push_back(glm::uvec3(0, 2, 3));

    background->vertexCount = 4;
    background->faceCount = 2;

    background->fillDefault();

    background->properties["vertex-shader"] = "./res/Background.vert";
    background->properties["fragment-shader"] = "./res/Background.frag";

    generateBuffer(background);
    defaultMeshes.push_back(background);

    // ================ END TEST ================

    init = true;
}

void GLRenderer::generateBuffer(Mesh * mesh) {
    // Make indexing space if necessary
    while (mesh->rendererIndex.size() <= rendererId) {
        mesh->rendererIndex.push_back(0);
    }
    // Check if the buffer has already been made
    if (mesh->rendererIndex[rendererId] == 0) {
        // Generate buffers
        GLBuffer glb(mesh);

        // Check for shaders, otherwise use default shader
        std::map<std::string, std::string>::const_iterator searchVert, searchFrag;
        searchVert = mesh->properties.find("vertex-shader");
        searchFrag = mesh->properties.find("fragment-shader");
        if (searchVert != mesh->properties.end() && searchFrag != mesh->properties.end()) {
            // Check if in the known shaders
            std::string key = "V:" + searchVert->second + ":F:" + searchFrag->second + ":";

            std::map<std::string, int>::const_iterator searchShader;
            searchShader = shaderFiles.find(key);
            if (searchShader == shaderFiles.end()) {
                // Create new shader
                GLShader gls;
                gls.load(searchVert->second, searchFrag->second);

                // Use new shader
                shaders.push_back(gls);
                glb.shaderIndex = shaders.size() - 1;

                // Add to known shaders
                shaderFiles[key] = shaders.size() - 1;
            }
            else {
                // Use known shader
                glb.shaderIndex = shaderFiles[key];
            }
        }
        else {
            // Use default shader
            shaders.push_back(shaders[0]);
            glb.shaderIndex = 0;
        }

        // Check for textures
        std::map<std::string, std::string>::const_iterator searchTexture;
        std::string tname;
        for (char i = '0'; i < '8'; i++) {
            tname = "texture";
            tname += i;
            searchTexture = mesh->properties.find(tname);
            if (searchTexture != mesh->properties.end()) {
                glb.loadTexture(searchTexture->second.c_str());
            }
            else {
                break;
            }
        }

        buffers.push_back(glb);
        mesh->rendererIndex[rendererId] = buffers.size() - 1;
    }
}
