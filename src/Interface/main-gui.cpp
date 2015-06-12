#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Windows.h>

#include "Pineapple/Pineapple.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Camera/PerspectiveCamera.hpp"

#define PI 3.141592653f

bool keys[512];
double prevMouseX, prevMouseY;
double scrollWheel;

static void error_callback(int error, const char* message) {
    fputs(message, stderr);
}

static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
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

static void mousewheel_callback(GLFWwindow * window, double scrollX, double scrollY) {
    scrollWheel += scrollX + scrollY;
}

static void handleInput(double duration, GLFWwindow * window, Camera * camera) {
    // Keys
    if (keys[GLFW_KEY_PERIOD]) {
        camera->setTarget(0.f, 0.f, 0.f);
    }

    // Mouse
    int mb;
    double mx, my;
    glfwGetCursorPos(window, &mx, &my);
    double dx = mx - prevMouseX;
    double dy = my - prevMouseY;

    // Rotation
    mb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (mb == GLFW_PRESS) {
        camera->rotate(dx, dy);
    }

    // Translation
    mb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (mb == GLFW_PRESS) {
        camera->translate(dx, dy);
    }

    prevMouseX = mx;
    prevMouseY = my;

    // Scroll wheel
    double scrollAmount = abs(scrollWheel);
    if (scrollAmount < 1) {
        camera->zoom(scrollWheel, 0.f);
        scrollWheel = 0;
    }
    else if (scrollAmount < 5) {
        if (scrollWheel < 0) {
            camera->zoom(-1, 0.f);
            scrollWheel += 1;
        }
        else {
            camera->zoom(1, 0.f);
            scrollWheel -= 1;
        }
    }
    else {
        if (scrollWheel < 0) {
            camera->zoom(-3, 0.f);
            scrollWheel += 3;
        }
        else {
            camera->zoom(3, 0.f);
            scrollWheel -= 3;
        }
    }
}

int main(void) {
    // Init GLFW
    
    if (!glfwInit()) {
        printf("glfw failed to initialize.");
        exit(EXIT_FAILURE);
    }
    
    glfwSetErrorCallback(error_callback);
    
    GLFWwindow * window = glfwCreateWindow(960, 540, "Pineapple Renderer", NULL, NULL);
    
    if (!window) {
        printf("glfw window failed to initialize.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, mousewheel_callback);
    
    if (glewInit() != GLEW_OK) {
        printf("glew failed to initialize.");
        exit(EXIT_FAILURE);
    }
    
    // Renderer variables
    Camera * c = new PerspectiveCamera(640, 480, 0.1f, 100.f, 45.f);
    c->setTarget(0.f, 0.f, 0.f);
    c->setPosition(4.f, 4.f, 4.f);
    Pineapple p;
    Scene * s = p.getScene();
    s->camera = c;
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
    
    // Initial inputs
    glfwGetCursorPos(window, &prevMouseX, &prevMouseY);

    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &newWidth, &newHeight);
        
        // Monitor for change in window size
        if (newWidth != width || newHeight != height) {
            s->setCameraViewport(newWidth, newHeight);
            width = newWidth;
            height = newHeight;
        }
        
        // Main rendering
        p.visualize();
        
        // Vsync or something?
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        // Some timing stuff
        currTime = glfwGetTime();
        duration = currTime - lastTime;
        if (duration < targetRate) {
            lastTime = currTime;
        }
        
        Sleep(16);

        if (currTime - lastFrame > 1.0) {
            printf("Frames per second: %d\n", frameCounter - lastFrameCount);
            //printf("Camera: %f %f %f\n", x, y, z);
            lastFrameCount = frameCounter;
            lastFrame = currTime;
        }
        
        frameCounter++;
        
        // Handle Input
        handleInput(duration, window, c);
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    
    return 0;
}
