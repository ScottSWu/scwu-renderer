#include <GLFW/glfw3.h>
#include <stdio.h>
#include <algorithm>

#include "Pineapple/Renderer/Renderer.hpp"
#include "Pineapple/Renderer/GLRenderer.hpp"
#include "Pineapple/Pineapple.hpp"

Pineapple::Pineapple() {
    visualizer = new GLRenderer();
}

Renderer * Pineapple::getRenderer() {
    return renderer;
}

void Pineapple::render(float imageBuffer[]) {
    renderer->render(imageBuffer);
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
    scene.push_back(object);
}

void Pineapple::removeObject(Object3d object) {
    scene.erase(
        std::remove(scene.begin(), scene.end(), object),
        scene.end()
    );
}
