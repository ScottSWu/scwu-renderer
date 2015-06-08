#include <GLFW/glfw3.h>
#include <stdio.h>
#include <algorithm>

#include "Pineapple/Renderer.hpp"
#include "Pineapple/Renderer/GLRenderer.hpp"
#include "Pineapple/Pineapple.hpp"

Pineapple::Pineapple() {
    visualizer = new GLRenderer();
}

Renderer * Pineapple::getRenderer() {
    return renderer;
}

void Pineapple::render(float imageBuffer[]) {
    renderer->render(imageBuffer, scene, camera, lights);
}

void Pineapple::visualize() {
    float dummy[1];
    visualizer->render(dummy, scene, camera, lights);
}

void Pineapple::setCameraViewport(int width, int height) {
    camera.viewport = glm::ivec2(width, height);
}

void Pineapple::setCameraPosition(float x, float y, float z) {
    camera.position = glm::vec3(x, y, z);
}

void Pineapple::setCameraTarget(float x, float y, float z) {
    camera.target = glm::vec3(x, y, z);
}

void Pineapple::addObject(Object3d object) {
    scene.addChild (object);
}

void Pineapple::removeObject(Object3d object) {
    scene.removeChild(object);
}

void Pineapple::addLight(Light light) {
    lights.push_back(light);
}

void Pineapple::removeLight(Light light) {
    lights.erase(std::remove(lights.begin(), lights.end(), light), lights.end());
}
