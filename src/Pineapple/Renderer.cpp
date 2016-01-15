#include "Pineapple/Renderer.hpp"

#include "Pineapple/Camera.hpp"
#include "Pineapple/RenderBuffer.hpp"
#include "Pineapple/RenderTask.hpp"
#include "Pineapple/Scene.hpp"

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

void Renderer::init(RenderBuffer * inBuffer, Scene * inScene) {
    currentBuffer = inBuffer;
    currentScene = inScene;
    currentCamera = inScene->getCamera();
    width = currentCamera->viewport.x;
    height = currentCamera->viewport.y;
}

void Renderer::render(RenderTask * task) {
    
}

void Renderer::process(RenderTask * task) {

}

bool Renderer::hasTask() {
    return false;
}

RenderTask * Renderer::getTask() {
    return new RenderTask(1, 1, 0, 0, 0);
}

int Renderer::getTaskCount() {
    return 0;
}
