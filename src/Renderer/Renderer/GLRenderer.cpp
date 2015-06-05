#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "Pineapple/Renderer.hpp"
#include "Pineapple/GLRenderer.hpp"
#include "Pineapple/Object3D.hpp"
#include "Pineapple/Mesh.hpp"
#include "Pineapple/GLShader.hpp"

GLRenderer::GLRenderer() : Renderer() {
    
}

/**
    Render scene to the current OpenGL context. Parameter for compatibility.

    @param dummy    Dummy variable to satisfy interface
*/
void GLRenderer::render (float dummy[]) {
    // Use built-in OpenGL for now
    renderBasic();
}

/**
    Do initialization stuff.
*/
void GLRenderer::initGL() {
    // Background color
    glClearColor(0.f, 0.f, 0.5f, 1.f);
    glEnable(GL_DEPTH_TEST);

    // TODO Provide functions for this stuff

    // Shader programs
    shader.load("./res/Diffuse.vert", "./res/Diffuse.frag");

    // Basic grid
    Mesh grid;

    // Vertices
    std::vector<glm::vec3> v;
    for (int i=-4; i<=4; i++) {
        v.push_back(glm::vec3(-4.f, 0.f, (float) i));
        v.push_back(glm::vec3( 4.f, 0.f, (float) i));
        v.push_back(glm::vec3( 4.f, 0.f, (float) i));
        v.push_back(glm::vec3((float) i, 0.f, -4.f));
        v.push_back(glm::vec3((float) i, 0.f,  4.f));
        v.push_back(glm::vec3((float) i, 0.f,  4.f));
    }
    grid.vertices.swap(v);

    // Normals
    std::vector<glm::vec3> n;
    for (int i=0; i<9 * 2 * 3; i++) {
        n.push_back(glm::vec3(0.f, 1.f, 0.f));
    }
    grid.vertexNormals.swap(n);

    // Indices
    std::vector<glm::uvec3> f;
    for (int i=0; i<9 * 2; i++) {
        f.push_back(glm::uvec3(3 * i + 0));
        f.push_back(glm::uvec3(3 * i + 1));
        f.push_back(glm::uvec3(3 * i + 2));
    }
    grid.faces.swap(f);

    grid.wireframe = true;

    GLBuffer gridBuffer(grid);

    buffers.push_back(gridBuffer);

    init = true;
}

/**
    Temporary basic rendering as a demo
*/
void GLRenderer::renderBasic() {
    if (!init) {
        initGL();
    }

    int width = camera.viewport.x;
    int height = camera.viewport.y;

    float ratio = (float) width / (float) height;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.bind();

    // Compute uniforms
    glm::mat4 mViewProjection = camera.computePerspectiveMatrix() * camera.computeCameraMatrix();
    glm::mat4 mTransform;
    glm::mat4 mTransformIT;

    glUniformMatrix4fv(shader.mViewProjectionId, 1, GL_FALSE, &mViewProjection[0][0]);
    glUniformMatrix4fv(shader.mTransformId, 1, GL_FALSE, &mTransform[0][0]);
    glUniformMatrix4fv(shader.mTransformITId, 1, GL_FALSE, &mTransformIT[0][0]);

    for (int i=0, l=buffers.size(); i<l; i++) {
        buffers[i].render();
    }

    shader.unbind();
}
