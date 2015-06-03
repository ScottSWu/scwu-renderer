#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "Pineapple/Renderer.hpp"
#include "Pineapple/GLRenderer.hpp"
#include "Pineapple/Mesh.hpp"

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
    glClearColor(0.f, 0.f 0.5f, 1.f);


    init = true;
}

void GLRenderer::renderBasic() {
    if (!init) {
        initGL();
    }

    int width = camera.viewport.x;
    int height = camera.viewport.y;

    float ratio = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.f, ratio, 0.1f, 100.f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, -2.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, -2.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, -2.f);
    glEnd();
}
