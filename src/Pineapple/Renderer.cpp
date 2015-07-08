#include "Pineapple/Renderer.hpp"

int Renderer::RENDERER_COUNT = 0;

Renderer::Renderer(std::map<std::string, std::string>) {
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
