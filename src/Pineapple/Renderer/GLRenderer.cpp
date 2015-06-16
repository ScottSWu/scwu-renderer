#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>

#include "Pineapple/Renderer/GLRenderer.hpp"
#include "Pineapple/Object3D.hpp"
#include "Pineapple/Camera.hpp"
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
    
    Camera * camera = scene->camera;
    
    int width = camera->viewport.x;
    int height = camera->viewport.y;
    
    float ratio = (float) width / (float) height;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Compute uniforms
    glm::mat4 mProjection = camera->computeProjectionMatrix();
    glm::mat4 mView = camera->computeCameraMatrix();
    glm::mat4 mProjectionView = mProjection * mView;

    // Render default objects
    GLShader defaultShader = shaders[0];
    defaultShader.bind();

    glUniformMatrix4fv(defaultShader.mProjectionViewId, 1, GL_FALSE, &mProjectionView[0][0]);
    glUniformMatrix4fv(defaultShader.mProjectionId, 1, GL_FALSE, &mProjection[0][0]);
    glUniformMatrix4fv(defaultShader.mViewId, 1, GL_FALSE, &mView[0][0]);
    
    int lastShader = 0;
    for (int i = 0, l = defaultBuffers.size(); i < l; i++) {
        renderBuffer(defaultBuffers[i], lastShader, mProjection, mView);
    }
    
    shaders[lastShader].unbind();
}

void GLRenderer::renderBuffer(GLBuffer & buffer, int & lastShader, glm::mat4 & mProjection, glm::mat4 & mView) {
    GLShader currentShader = shaders[lastShader];
    if (buffer.shaderIndex != lastShader) {
        // Bind new shader
        currentShader.unbind();
        currentShader = shaders[buffer.shaderIndex];
        currentShader.bind();

        glm::mat4 mProjectionView = mProjection * mView;
        glUniformMatrix4fv(currentShader.mProjectionViewId, 1, GL_FALSE, &mProjectionView[0][0]);
        glUniformMatrix4fv(currentShader.mProjectionId, 1, GL_FALSE, &mProjection[0][0]);
        glUniformMatrix4fv(currentShader.mViewId, 1, GL_FALSE, &mView[0][0]);
    }
    glm::mat4 mTransform;
    glm::mat4 mTransformIT;
    glUniformMatrix4fv(currentShader.mTransformId, 1, GL_FALSE, &mTransform[0][0]);
    glUniformMatrix4fv(currentShader.mTransformITId, 1, GL_FALSE, &mTransformIT[0][0]);

    buffer.render();
}

void GLRenderer::initGL() {
    // Background color
    glClearColor(0.f, 0.f, 0.5f, 1.f);
    glEnable(GL_DEPTH_TEST);
    
    // TODO Provide functions for this stuff
    
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

    GLBuffer gridBuffer(grid);

    defaultBuffers.push_back(gridBuffer);

    // ================ END TEST ================

    init = true;
}

void GLRenderer::generateBuffers(Object3d * o) {
    Mesh * m = dynamic_cast<Mesh*>(o);
    if (m != 0) {
        // Make indexing space if necessary
        if (m->rendererIndex.size() <= rendererId) {
            m->rendererIndex.reserve(rendererId + 1);
        }
        // Check if the buffer has already been made
        if (m->rendererIndex[rendererId] == 0) {
            // Generate buffers
            GLBuffer glb(m);
            buffers.push_back(glb);
            m->rendererIndex[rendererId] = buffers.size() - 1;

            // Check for shaders, otherwise use default shader
            std::map<std::string, std::string>::const_iterator searchVert, searchFrag;
            searchVert = m->properties.find("vertex-shader");
            searchFrag = m->properties.find("fragment-shader");
            if (searchVert != m->properties.end() && searchFrag != m->properties.end()) {
                // Check if in the known shaders
                std::string key = "V:" + searchVert->second + ":F:" + searchFrag->second + ":";

                std::map<std::string, int>::const_iterator searchShader;
                searchShader = shaderFiles.find(key);
                if (searchShader != shaderFiles.end()) {
                    // Create new shader
                    GLShader gls;
                    gls.load(searchVert->second, searchFrag->second);
                    shaders.push_back(gls);

                    // Use new shader
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
        }
    }
    // Generate buffers for children
    for (int i = 0, l = o->children.size(); i < l; i++) {
        generateBuffers(o->children[i]);
    }
}
