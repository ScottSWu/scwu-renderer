#include "Pineapple/Renderer.hpp"

int Renderer::RENDERER_COUNT = 0;
int Renderer::rendererId = -1;

Renderer::Renderer() {
    registerRenderer();
}

void Renderer::registerRenderer() {
    rendererId = RENDERER_COUNT++;
}

void Renderer::render(float imageBuffer[], Object3d scene, Camera camera, std::vector<Light> lights) {

}
