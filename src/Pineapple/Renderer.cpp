#include <vector>

#include "Pineapple/Camera.hpp"
#include "Pineapple/Light.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/Renderer.hpp"

int Renderer::RENDERER_COUNT = 0;

Renderer::Renderer() {
    rendererId = -1;
    registerRenderer();
}

Renderer::~Renderer() {
    
}

void Renderer::registerRenderer() {
    rendererId = ++RENDERER_COUNT;
}

void Renderer::render(float imageBuffer[], Scene * scene) {
    
}
