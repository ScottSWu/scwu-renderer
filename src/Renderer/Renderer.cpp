#include "Pineapple/Renderer.hpp"

Renderer::Renderer() {

}

void Renderer::render(float imageBuffer[]) {
    
}

void Renderer::setViewport(int width, int height) {
    camera.viewport = glm::ivec2(width, height);
}
