#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define NOMINMAX

#include "resources.h"
#include "Pineapple/Pineapple.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Camera/PerspectiveCamera.hpp"
#include "Pineapple/Scene.hpp"
#include "Pineapple/Util/LoadObjFile.hpp"

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <glm/glm.hpp>
#include <tiny_obj_loader.h>
#include <FreeImage.h>

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

#include <windows.h>
#include <Commdlg.h>

#define PI 3.141592653f

GLFWwindow * window;
Pineapple p;
Scene * s;
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
    if (keys[GLFW_KEY_W]) {
        camera->move(5.f, 0.f);
    }
    if (keys[GLFW_KEY_S]) {
        camera->move(-5.f, 0.f);
    }
    if (keys[GLFW_KEY_D]) {
        camera->move(0.f, 5.f);
    }
    if (keys[GLFW_KEY_A]) {
        camera->move(0.f, -5.f);
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

    // Move
    mb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (mb == GLFW_PRESS) {
        camera->look(dx, dy);
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

void requestSaveImage(HWND hwnd, int width, int height, float imageBuffer[]) {
    OPENFILENAME ofn;
    char filename[260];
    filename[0] = '\0';
    ZeroMemory( &ofn , sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "*.png\0";
    ofn.lpstrFile = filename;
    ofn.nFilterIndex = 1;
    ofn.nMaxFile = 260;
    ofn.Flags = OFN_PATHMUSTEXIST;

    // Save current working directory
    TCHAR cwd[260];
    GetCurrentDirectory(260, cwd);

    bool confirm = GetSaveFileName(&ofn);

    // Restore working directory
    SetCurrentDirectory(cwd);

    if (confirm) {
        FIBITMAP * bitmap = FreeImage_Allocate(width, height, 32,
        FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
        if (bitmap) {
            int offset = 0;
            for (int i = 0; i < height; i++) {
                BYTE * line = FreeImage_GetScanLine(bitmap, i);
                for (int j = 0; j < width; j++) {
                    line[FI_RGBA_RED] = (int) (imageBuffer[offset + 0] * 255);
                    line[FI_RGBA_GREEN] = (int) (imageBuffer[offset + 1] * 255);
                    line[FI_RGBA_BLUE] = (int) (imageBuffer[offset + 2] * 255);
                    line[FI_RGBA_ALPHA] = (int) (imageBuffer[offset + 3] * 255);
                    line += 4;
                    offset += 4;
                }
            }

            // Save and clean up
            FreeImage_Save(FIF_PNG, bitmap, filename, 0);
        }
        FreeImage_Unload(bitmap);
    }
}

/**
 * Handle windows input
 */
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
        case WM_COMMAND:
            switch (LOWORD(wparam)) {
                case ID_MENU_FILE_OPEN: {
                    OPENFILENAME ofn;
                    char filename[260];
                    filename[0] = '\0';
                    ZeroMemory( &ofn , sizeof(ofn));

                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = hwnd;
                    ofn.lpstrFilter = "*.obj\0*.obj\0All\0*.*\0";
                    ofn.lpstrFile = filename;
                    ofn.nFilterIndex = 1;
                    ofn.nMaxFile = 260;
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                    // Save current working directory
                    TCHAR cwd[260];
                    GetCurrentDirectory(260, cwd);

                    bool confirm = GetOpenFileName(&ofn);

                    // Restore working directory
                    SetCurrentDirectory(cwd);

                    if (confirm) {
                        char foldername[260];
                        int len = 0;
                        while (filename[len] != '\0') {
                            foldername[len] = filename[len];
                            len++;
                        }
                        foldername[len] = '\0';
                        while (len >= 0 && foldername[len] != '\\') {
                            foldername[len] = '\0';
                            len--;
                        }

                        std::vector<Object3d *> objects = LoadObjFile(filename, foldername);
                        for (std::vector<Object3d *>::iterator i = objects.begin(); i != objects.end(); i++) {
                            s->addObject(*i);
                        }
                    }

                    // Restore working directory
                    SetCurrentDirectory(cwd);
                }
                    break;
                case ID_MENU_FILE_EXIT:
                    glfwSetWindowShouldClose(window, GL_TRUE);
                    break;
                case ID_MENU_RENDER_OPENGL:
                    // TODO Render OpenGL
                    break;
                case ID_MENU_RENDER_DEPTH: {
                    std::map<std::string, std::string> params;
                    params["type"] = "raycast";
                    params["integrator"] = "depth";
                    p.setRenderer(params);

                    // Prepare the image buffer
                    Camera * c = s->getCamera();
                    int width = c->viewport.x;
                    int height = c->viewport.y;
                    float * imageBuffer = new float[width * height * 4];
                    p.render(imageBuffer);

                    requestSaveImage(hwnd, width, height, imageBuffer);
                }
                    break;
                case ID_MENU_RENDER_COLOR: {
                    std::map<std::string, std::string> params;
                    params["type"] = "raycast";
                    params["integrator"] = "color";
                    p.setRenderer(params);

                    // Prepare the image buffer
                    Camera * c = s->getCamera();
                    int width = c->viewport.x;
                    int height = c->viewport.y;
                    float * imageBuffer = new float[width * height * 4];
                    p.render(imageBuffer);

                    requestSaveImage(hwnd, width, height, imageBuffer);
                }
                    break;
                default:
                    break;
            }
            break;
        default:
            // If nothing was handled, pass to glfw
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
    s = p.getScene();
    Camera * c = new PerspectiveCamera(960, 540, 1.f, 100.f, 45.f);
    c->setTarget(0.f, 0.f, 0.f);
    c->setPosition(4.f, 4.f, 4.f);
    s->setCamera(c);

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

        // Events
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
