#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define NOMINMAX

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <glm/glm.hpp>
#include <tiny_obj_loader.h>

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#include <windows.h>
#include <Commdlg.h>

#include "Pineapple/Pineapple.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Camera/PerspectiveCamera.hpp"
#include "resources.h"

#define PI 3.141592653f

GLFWwindow * window;
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
    mb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
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

/**
 * Handle windows input
 */
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wparam)) {
                case ID_MENU_FILE_OPEN:
                    OPENFILENAME ofn;
                    char filename[260];
                    ZeroMemory( &ofn , sizeof(ofn));
                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = NULL;
                    ofn.lpstrFile = filename;
                    ofn.lpstrFile[0] = '\0';
                    ofn.nMaxFile = sizeof(filename);
                    ofn.lpstrFilter = "obj\0*.obj\0All\0*.*\0";
                    ofn.nFilterIndex = 1;
                    ofn.lpstrFileTitle = NULL;
                    ofn.nMaxFileTitle = 0;
                    ofn.lpstrInitialDir = NULL;
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                    if (GetOpenFileName(&ofn)) {
                        std::vector<tinyobj::shape_t> shapes;
                        std::vector<tinyobj::material_t> materials;
                        std::string err = tinyobj::LoadObj(shapes, materials, filename);

                        if (!err.empty()) {
                            std::cout << err << std::endl;
                        }
                    }
                    break;
                case ID_MENU_FILE_EXIT:
                    glfwSetWindowShouldClose(window, GL_TRUE);
                    break;
            }
            break;
        default:
            return glfwWindowProc(hwnd, msg, wparam, lparam);
    }

    // Pass call to glfw
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Init GLFW
    if (!glfwInit()) {
        printf("glfw failed to initialize.");
        exit(EXIT_FAILURE);
    }
    
    glfwSetErrorCallback(error_callback);
    
    window = glfwCreateWindow(960, 540, "Pineapple Renderer", NULL, NULL);
    
    if (!window) {
        printf("glfw window failed to initialize.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Some stuff
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, mousewheel_callback);
    
    // Init glew
    if (glewInit() != GLEW_OK) {
        printf("glew failed to initialize.");
        exit(EXIT_FAILURE);
    }
    
    // Init windows menu bars and stuff
    WNDPROC hProc;
    HWND hWindow;
    HMENU hMenu;

    hWindow = glfwGetWin32Window(window);
    hProc = (WNDPROC) GetWindowLongPtr(hWindow, GWL_WNDPROC);
    SetWindowLongPtr(hWindow, GWL_WNDPROC, (long) WinProc);

    // Set menu
    hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(ID_MENU));
    SetMenu(hWindow, hMenu);

    // Set icons
    HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_ICON));
    if (hIcon) {
        SendMessage(hWindow, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
    }
    HICON hIconSm = (HICON) LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(ID_ICON), IMAGE_ICON, 16, 16, 0);
    if (hIconSm) {
        SendMessage(hWindow, WM_SETICON, ICON_SMALL, (LPARAM) hIconSm);
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
