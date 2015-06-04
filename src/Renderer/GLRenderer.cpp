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
*/
void GLRenderer::render (float dummy[]) {
    // Use built-in OpenGL for now
    renderBasic();
}

void GLRenderer::initGL() {
    // Background color
    glClearColor(0.f, 0.f, 0.5f, 1.f);

    // Shader programs
    shader.load("./res/Diffuse.vert", "./res/Diffuse.frag");
    
    // Basic grid
    Mesh grid;
    
    std::vector<glm::vec3> v;
    v.push_back(glm::vec3(-0.5f, 0.f, -0.3f));
    v.push_back(glm::vec3( 0.5f, 0.f, -0.3f));
    v.push_back(glm::vec3( 0.0f, 0.f,  0.6f));
    grid.vertices.swap(v);
    
    std::vector<glm::vec3> n;
    n.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    n.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    n.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    grid.vertexNormals.swap(n);
    
    std::vector<glm::uvec3> f;
    f.push_back(glm::uvec3(0, 1, 2));
    grid.faces.swap(f);
    
    GLBuffer gridBuffer(grid);
    
    buffers.push_back(gridBuffer);

    init = true;
}

bool first = true;

void GLRenderer::renderBasic() {
    if (!init) {
        initGL();
    }

    int width = camera.viewport.x;
    int height = camera.viewport.y;

    float ratio = (float) width / (float) height;
    glClear(GL_COLOR_BUFFER_BIT);
    
    shader.bind();
    
    // Compute uniforms
    glm::mat4 mViewProjection = camera.computePerspectiveMatrix() * camera.computeCameraMatrix();
    glm::mat4 mTransform;
    glm::mat4 mTransformIT;
    
    if (first) {
        
        first = false;
    }
    
    glUniformMatrix4fv(shader.mViewProjectionId, 1, GL_FALSE, &mViewProjection[0][0]);
    glUniformMatrix4fv(shader.mTransformId, 1, GL_FALSE, &mTransform[0][0]);
    glUniformMatrix4fv(shader.mTransformITId, 1, GL_FALSE, &mTransformIT[0][0]);
    
    for (int i=0, l=buffers.size(); i<l; i++) {
        buffers[i].render();
    }
    
    shader.unbind();
}
