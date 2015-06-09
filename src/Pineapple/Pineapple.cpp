#include <GLFW/glfw3.h>
#include <stdio.h>
#include <algorithm>

#include "Pineapple/Light.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/Renderer.hpp"
#include "Pineapple/Renderer/GLRenderer.hpp"
#include "Pineapple/Pineapple.hpp"

Pineapple::Pineapple() {
    renderer = new Renderer();
    visualizer = new GLRenderer();
    scene = new Scene();
}

Renderer * Pineapple::getRenderer() {
    return renderer;
}

Scene * Pineapple::getScene() {
    return scene;
}

void Pineapple::render(float imageBuffer[]) {
    renderer->render(imageBuffer, scene);
}

void Pineapple::visualize() {
    float dummy[1];
    visualizer->render(dummy, scene);
}
