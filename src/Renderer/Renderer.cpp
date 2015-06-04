#include "Pineapple/Renderer.hpp"

Renderer::Renderer() {

}

void Renderer::render(float imageBuffer[]) {
    
}

void Renderer::setCameraViewport(int width, int height) {
    camera.viewport = glm::ivec2(width, height);
}

void Renderer::setCameraPosition(float x, float y, float z) {
    camera.position = glm::vec3(x, y, z);
}
