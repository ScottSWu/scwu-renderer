#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Windows.h>

#include "Placeholder/Placeholder.hpp"

#define PI 3.141592653f

bool keys[512];
glm::vec3 cam = glm::vec3(PI/4.f, PI/6.f, 8.f);

static void error_callback(int error, const char* message) {
    fputs(message, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (action == GLFW_PRESS) {
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
}

static void handleKeys() {
    if (keys[GLFW_KEY_UP]) {
        cam.y += 0.04;
    }
    else if (keys[GLFW_KEY_DOWN]) {
        cam.y -= 0.04;
    }

    if (keys[GLFW_KEY_LEFT]) {
        cam.x += 0.04;
    }
    else if (keys[GLFW_KEY_RIGHT]) {
        cam.x -= 0.04;
    }

    if (cam.y>PI/2.f - 0.1f) {
        cam.y = PI/2.f - 0.1f;
    }
    else if (cam.y<-PI/2.f + 0.1f) {
        cam.y = -PI/2.f + 0.1f;
    }

    cam.x = (float) fmod(cam.x, 2.f * PI);
}

int main(void) {
    // Init GLFW

    if (!glfwInit()) {
        printf("glfw failed to initialize.");
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Renderer", NULL, NULL);

    if (!window) {
        printf("glfw window failed to initialize.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

    if (glewInit() != GLEW_OK) {
        printf("glew failed to initialize.");
        exit(EXIT_FAILURE);
    }

    // Renderer variables
    Placeholder p;
    Renderer * r = p.getRenderer();
    int width, height, newWidth, newHeight;
    float dummy[1];

    // Timing variables
    double targetRate = 1.0 / 60.0;
    double lastTime = glfwGetTime();
    double currTime = lastTime;
    double duration;
    long lastFrameCount = 0;
    double lastFrame = currTime;
    long frameCounter = 0;

    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &newWidth, &newHeight);

        // Monitor for change in window size
        if (newWidth!=width || newHeight!=height) {
            r->setCameraViewport(newWidth, newHeight);
            width = newWidth;
            height = newHeight;
        }

        // Set and update camera orientation
        float x = (float) (cam.z * cos(cam.y) * cos(cam.x));
        float y = (float) (cam.z * sin(cam.y));
        float z = (float) (cam.z * cos(cam.y) * sin(cam.x));
        r->setCameraPosition(x, y, z);
        r->setCameraTarget(0.f, 0.f, 0.f);


        // Main rendering
        p.render(dummy);

        // Vsync or something?
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Some timing stuff
        currTime = glfwGetTime();
        duration = currTime - lastTime;
        if (duration < targetRate) {
            Sleep((int) ((targetRate - duration) * 1000));
            lastTime = currTime;
        }

        if (currTime - lastFrame > 1.0) {
            printf("Frames per second: %d\n", frameCounter - lastFrameCount);
            lastFrameCount = frameCounter;
            lastFrame = currTime;
        }

        frameCounter++;

        // Handle keys
        handleKeys();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);

    return 0;
}