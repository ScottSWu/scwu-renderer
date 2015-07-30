#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define NOMINMAX

#include "resources.h"
#include "Pineapple/Pineapple.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Camera/PerspectiveCamera.hpp"
#include "Pineapple/Scene.hpp"
#include "Pineapple/RenderBuffer.hpp"
#include "Pineapple/Util/LoadObjFile.hpp"
#include "Pineapple/Util/LoadJSONFile.hpp"

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <tiny_obj_loader.h>
#include <FreeImage.h>

#include <chrono>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <mutex>
#include <thread>

#include <windows.h>
#include <Commdlg.h>

#define PI 3.141592653f

GLFWwindow * window;
Pineapple p;
Scene * s;

int currentView;
bool keys[512];
double prevMouseX, prevMouseY;
double scrollWheel;

RenderBuffer * output;
GLuint texId = 0;
GLuint fbId = 0;

WNDPROC hProc;
HWND hWindow;
HMENU hMenu;

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
            // Clamp all values between 0 and 1
            for (int i = 0, l = width * height * 4; i < l; i++) {
                if (imageBuffer[i] < 0.f) {
                    imageBuffer[i] = 0.f;
                }
                else if (imageBuffer[i] > 1.f) {
                    imageBuffer[i] = 1.f;
                }
            }

            // Write to bitmap
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
 * Render and save result
 */
void sideRender(HWND hwnd) {
    auto startTime = std::chrono::high_resolution_clock::now();
    if (p.render()) {
        auto endTime = std::chrono::high_resolution_clock::now();
        printf("Time: %i ms\n", std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());

        RenderBuffer * result = p.getRenderBuffer();

        requestSaveImage(hwnd, result->width, result->height, result->buffer);
    }
}

bool hasExtension(const char * s, int l, const char * e, int m) {
    l--;
    m--;
    while (l >= 0 && m >= 0) {
        // Get characters
        char sc = s[l];
        char se = e[m];
        // Upper case
        if (sc >= 'a' && sc <= 'z') {
            sc = sc - 32;
        }
        if (se >= 'a' && se <= 'z') {
            se = se - 32;
        }
        // False if they don't match
        if (sc != se) {
            return false;
        }
        // Check next characters
        l--;
        m--;
    }
    return true;
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
                    ofn.lpstrFilter = "JSON Scene\0*.json\0Object File\0*.obj\0All\0*.*\0";
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
                        int folderlen = len;
                        while (folderlen >= 0 && foldername[folderlen] != '\\') {
                            foldername[folderlen] = '\0';
                            folderlen--;
                        }

                        // Check extension and load accordingly
                        if (hasExtension(filename, len, ".obj", 4)) {
                            std::vector<Object3d *> objects = LoadObjFile(filename, foldername);
                            for (std::vector<Object3d *>::iterator i = objects.begin(); i != objects.end(); i++) {
                                s->addObject(*i);
                            }
                        }
                        else if (hasExtension(filename, len, ".json", 5)) {
                            LoadJSONFile(s, filename, foldername);
                            // Set the proper window size afterwards, accounting for menu bar(?)
                            Camera * c = p.getScene()->getCamera();
                            glfwSetWindowSize(window, c->viewport.x, c->viewport.y + 25);
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

                    // Clear output
                    glDeleteTextures(1, &texId);
                    glDeleteFramebuffers(1, &fbId);
                    texId = 0;
                    fbId = 0;
                    output = new RenderBuffer();

                    std::thread(sideRender, hwnd).detach();
                }
                    break;
                case ID_MENU_RENDER_COLOR: {
                    std::map<std::string, std::string> params;
                    params["type"] = "raycast";
                    params["integrator"] = "color";
                    p.setRenderer(params);

                    // Clear output
                    glDeleteTextures(1, &texId);
                    glDeleteFramebuffers(1, &fbId);
                    texId = 0;
                    fbId = 0;
                    output = new RenderBuffer();

                    std::thread(sideRender, hwnd).detach();
                }
                    break;
                case ID_MENU_RENDER_MATERIAL: {
                    std::map<std::string, std::string> params;
                    params["type"] = "raycast";
                    params["integrator"] = "material";
                    p.setRenderer(params);

                    // Clear output
                    glDeleteTextures(1, &texId);
                    glDeleteFramebuffers(1, &fbId);
                    texId = 0;
                    fbId = 0;
                    output = new RenderBuffer();

                    std::thread(sideRender, hwnd).detach();
                }
                    break;
                case ID_MENU_RENDER_MATERIALMP: {
                    std::map<std::string, std::string> params;
                    params["type"] = "raycast";
                    params["integrator"] = "material";
                    params["cores"] = std::to_string(std::thread::hardware_concurrency());
                    params["samples"] = "4";
                    p.setRenderer(params);

                    // Clear output
                    glDeleteTextures(1, &texId);
                    glDeleteFramebuffers(1, &fbId);
                    texId = 0;
                    fbId = 0;
                    output = new RenderBuffer();

                    std::thread(sideRender, hwnd).detach();
                }
                    break;

                case ID_MENU_VIEW_SCENE: {
                    currentView = 0;
                }
                    break;
                case ID_MENU_VIEW_RENDER: {
                    currentView = 1;
                }
                    break;
                default:
                    break;
            }
            break;
        default:
            // If nothing was handled, pass to glfw
            return CallWindowProc(hProc, hwnd, msg, wparam, lparam);
    }

    // Pass call to default
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

/**
 * Main function
 */
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
    
    // Init windows stuff
    hWindow = glfwGetWin32Window(window);
    hProc = (WNDPROC) GetWindowLongPtr(hWindow, GWLP_WNDPROC);
    SetWindowLongPtr(hWindow, GWLP_WNDPROC, (long long int) WinProc);

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
        
        // Switch views
        if (currentView == 0) { // Visualization
            p.visualize();
        }
        else if (currentView == 1) { // Render
            if (output == 0) {
                output = new RenderBuffer();
            }

            if (output->width == 0 && output->height == 0) {
                output = p.getRenderBuffer();
            }
            else {
                if (texId == 0) {
                    glGenTextures(1, &texId);
                    glBindTexture(GL_TEXTURE_2D, texId);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, output->width, output->height, 0, GL_RGBA, GL_FLOAT,
                            &output->buffer[0]);
                    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, output->width, output->height);
                }
                if (fbId == 0) {
                    glGenFramebuffers(1, &fbId);
                    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbId);
                    glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);
                    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
                }
            }

            int ow = output->width;
            int oh = output->height;
            float * ob = output->buffer;
            glBindTexture(GL_TEXTURE_2D, texId);

            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ow, oh, GL_RGBA, GL_FLOAT, ob);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glBindFramebuffer(GL_READ_FRAMEBUFFER, fbId);
            glBlitFramebuffer(0, 0, ow, oh, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
            glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

            glBindTexture(GL_TEXTURE_2D, 0);
        }
        
        // Vsync
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
        handleInput(duration, window, s->getCamera());
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    
    return 0;
}
