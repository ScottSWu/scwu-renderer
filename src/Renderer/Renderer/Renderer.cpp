#include "Pineapple/Renderer/Renderer.hpp"

Renderer::Renderer() {
    registerRenderer();
}

void Renderer::registerRenderer() {
    rendererId = RENDERER_COUNT++;
}

void Renderer::render(float imageBuffer[]) {

}
