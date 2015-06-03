#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include "Pineapple/Pineapple.hpp"

static void error_callback(int error, const char* message) {
    fputs(message, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(void) {
    // Init GLFW

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Renderer", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

    Pineapple p;
    int width, height, newWidth, newHeight;
    float dummy[1];
    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &newWidth, &newHeight);

        if (newWidth!=width || newHeight!=height) {
            p.getRenderer()->setViewport(newWidth, newHeight);
            width = newWidth;
            height = newHeight;
        }

        p.render(dummy);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}
