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

void GLRenderer::render(float imageBuffer[], Scene * scene) {
    if (!init) {
        initGL(scene);
    }
    
    Camera camera = scene->getCamera();

    int width = camera.viewport.x;
    int height = camera.viewport.y;
    
    float ratio = (float) width / (float) height;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shader.bind();
    
    // Compute uniforms
    glm::mat4 mViewProjection = camera.computeProjectionMatrix() * camera.computeCameraMatrix();
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

    // Create buffers
    generateBuffers(scene->getObjects());

    /**
     // Basic grid
     Mesh grid;
     
     // Vertices
     std::vector<glm::vec3> v;
     for (int i = -4; i <= 4; i++) {
     v.push_back(glm::vec3(-4.f, 0.f, (float) i));
     v.push_back(glm::vec3(4.f, 0.f, (float) i));
     v.push_back(glm::vec3(4.f, 0.f, (float) i));
     v.push_back(glm::vec3((float) i, 0.f, -4.f));
     v.push_back(glm::vec3((float) i, 0.f, 4.f));
     v.push_back(glm::vec3((float) i, 0.f, 4.f));
     }
     grid.vertices.swap(v);
     
     // Normals
     std::vector<glm::vec3> n;
     for (int i = 0; i < 9 * 2 * 3; i++) {
     n.push_back(glm::vec3(0.f, 1.f, 0.f));
     }
     grid.vertexNormals.swap(n);
     
     // Indices
     std::vector<glm::uvec3> f;
     for (int i = 0; i < 9 * 2; i++) {
     f.push_back(glm::uvec3(3 * i + 0));
     f.push_back(glm::uvec3(3 * i + 1));
     f.push_back(glm::uvec3(3 * i + 2));
     }
     grid.faces.swap(f);
     
     grid.wireframe = true;
     
     GLBuffer gridBuffer(grid);
     
     buffers.push_back(gridBuffer);
     */

    init = true;
}

void generateBuffers(std::vector<Object3d> objects) {

}
