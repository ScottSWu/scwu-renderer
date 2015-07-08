#include "Pineapple/Renderer/GLRenderer.hpp"

#include "Pineapple/Camera.hpp"
#include "Pineapple/Camera/PerspectiveCamera.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Light.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/Renderer/GLBuffer.hpp"
#include "Pineapple/Renderer/GLShader.hpp"
#include "Pineapple/Renderer/GLUniforms.hpp"
#include "Pineapple/Scene.hpp"
#include "Pineapple/Shape/Mesh.hpp"

GLRenderer::GLRenderer(std::map<std::string, std::string> parameters) :
        Renderer(parameters) {
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

    float ratio = (float) width / (float) height;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, width, height);
    
    // Compute uniforms
    GLUniforms uniforms(scene, camera);

    // Use the default shader
    GLShader defaultShader = shaders[0];
    defaultShader.bind();
    uniforms.bind(defaultShader);
    
    //printf("Loop\n");
    // Render default objects
    int lastShader = 0;
    for (int i = 0, l = defaultMeshes.size(); i < l; i++) {
        renderObject(defaultMeshes[i], lastShader, uniforms);
    }
    
    // Render scene objects
    std::vector<Object3d *> objects = scene->getObjects();
    for (int i = 0, l = objects.size(); i < l; i++) {
        renderObject(objects[i], lastShader, uniforms);
    }

    shaders[lastShader].unbind();
}

void GLRenderer::renderObject(Object3d * object, int & lastShader, GLUniforms & uniforms) {
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
        renderBuffer(buffers[bufferIndex], lastShader, uniforms);
    }

    for (int i = 0, l = object->children.size(); i < l; i++) {
        renderObject(object->children[i], lastShader, uniforms);
    }
}

void GLRenderer::renderBuffer(GLBuffer & buffer, int & lastShader, GLUniforms & uniforms) {
    GLShader currentShader = shaders[lastShader];
    if (buffer.shaderIndex != lastShader) {
        // Bind new shader
        currentShader.unbind();
        currentShader = shaders[buffer.shaderIndex];
        currentShader.bind();

        uniforms.bind(currentShader);

        lastShader = buffer.shaderIndex;
    }
    // TODO Compute and use object matrix transforms
    glm::mat4 mTransform;
    glm::mat4 mTransformIT;
    glUniformMatrix4fv(currentShader.mTransformId, 1, GL_FALSE, &mTransform[0][0]);
    glUniformMatrix4fv(currentShader.mTransformITId, 1, GL_FALSE, &mTransformIT[0][0]);

    buffer.bind(currentShader);
    buffer.render();
    buffer.unbind();
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
    grid->material->properties["vertex-shader"] = "./res/Line.vert";
    grid->material->properties["fragment-shader"] = "./res/Line.frag";

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

    background->material->properties["vertex-shader"] = "./res/Background.vert";
    background->material->properties["fragment-shader"] = "./res/Background.frag";

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
        Material * mat = mesh->material;
        std::map<std::string, std::string>::const_iterator searchVert, searchFrag;
        searchVert = mat->properties.find("vertex-shader");
        searchFrag = mat->properties.find("fragment-shader");
        if (searchVert != mat->properties.end() && searchFrag != mat->properties.end()) {
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
        for (int i = 0; i < mat->textures.size(); i++) {
            glb.loadTexture(mat->textures[i]);
        }

        buffers.push_back(glb);
        mesh->rendererIndex[rendererId] = buffers.size() - 1;
    }
}
