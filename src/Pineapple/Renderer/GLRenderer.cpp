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
    mViewProjectionId = -1;
    mTransformId = -1;
    mTransformITId = -1;
}

GLRenderer::~GLRenderer() {
    
}

bool _tmp_first = true;
void GLRenderer::render(float imageBuffer[], Scene * scene) {
    if (!init) {
        initGL(scene);
    }
    
    Camera * camera = scene->camera;
    
    int width = camera->viewport.x;
    int height = camera->viewport.y;
    
    float ratio = (float) width / (float) height;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shader.bind();
    
    // Compute uniforms
    glm::mat4 mViewProjection = camera->computeProjectionMatrix() * camera->computeCameraMatrix();
    glm::mat4 mTransform;
    glm::mat4 mTransformIT;

    glUniformMatrix4fv(mViewProjectionId, 1, GL_FALSE, &mViewProjection[0][0]);
    glUniformMatrix4fv(mTransformId, 1, GL_FALSE, &mTransform[0][0]);
    glUniformMatrix4fv(mTransformITId, 1, GL_FALSE, &mTransformIT[0][0]);
    
    for (int i = 0, l = buffers.size(); i < l; i++) {
        buffers[i].render();
    }
    
    shader.unbind();
}

void GLRenderer::initGL(Scene * scene) {
    // Background color
    glClearColor(0.f, 0.f, 0.5f, 1.f);
    glEnable(GL_DEPTH_TEST);
    
    // TODO Provide functions for this stuff
    
    // Shader program and uniforms
    shader.load("./res/Diffuse.vert", "./res/Diffuse.frag");
    mViewProjectionId = shader.getUniformLocation("mViewProjection");
    mTransformId = shader.getUniformLocation("mTransform");
    mTransformITId = shader.getUniformLocation("mTransformIT");
    //printf("%d %d %d\n", mViewProjectionId, mTransformId, mTransformITId);
    
    // Create buffers
    generateBuffers(scene->getObjects());
    
    // ================ TEST ================
    // Basic grid
    Mesh grid;

    for (int i = -4; i <= 4; i++) {
        grid.positions.push_back(glm::vec4(-4.f, 0.f, (float) i, 1.f));
        grid.normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid.positions.push_back(glm::vec4(4.f, 0.f, (float) i, 1.f));
        grid.normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid.positions.push_back(glm::vec4(4.f, 0.f, (float) i, 1.f));
        grid.normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid.positions.push_back(glm::vec4((float) i, 0.f, -4.f, 1.f));
        grid.normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid.positions.push_back(glm::vec4((float) i, 0.f, 4.f, 1.f));
        grid.normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid.positions.push_back(glm::vec4((float) i, 0.f, 4.f, 1.f));
        grid.normals.push_back(glm::vec4(0.f, 1.f, 0.f, 1.f));

        grid.vertexCount += 6;
    }

    grid.fillDefault();

    // Indices
    for (unsigned int i = 0; i < 9 * 2; i++) {
        grid.faces.push_back(glm::uvec3(3 * i + 0, 3 * i + 1, 3 * i + 2));
        grid.faceCount++;
    }

    grid.wireframe = true;

    GLBuffer gridBuffer(grid);

    buffers.push_back(gridBuffer);

    // ================ END TEST ================

    init = true;
}

void GLRenderer::generateBuffers(std::vector<Object3d> & objects) {
    /*
     for (int i = 0, l = objects.size(); i < l; i++) {
     Object3d o = objects[i];
     Mesh * m = dynamic_cast<Mesh*>(&o);
     if (m != 0) {
     GLBuffer glb(m);
     buffers.push_back(glb);
     }
     generateBuffers(objects[i].children);
     }
     */
}
