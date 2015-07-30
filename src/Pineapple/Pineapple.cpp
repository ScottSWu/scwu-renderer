#include "Pineapple/Pineapple.hpp"

#include "Pineapple/Camera.hpp"
#include "Pineapple/Light.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/RenderBuffer.hpp"
#include "Pineapple/Renderer.hpp"
#include "Pineapple/Renderer/GLRenderer.hpp"
#include "Pineapple/Renderer/Raycaster.hpp"
#include "Pineapple/RenderTask.hpp"
#include "Pineapple/Scene.hpp"
#include "Pineapple/TaskRunner.hpp"
#include "Pineapple/Task/MPTaskRunner.hpp"

Pineapple::Pineapple() {
    std::map<std::string, std::string> params;
    renderer = new Renderer(params);
    visualizer = new GLRenderer(params);
    scene = new Scene();
    currentBuffer = new RenderBuffer(0, 0, new float[0]);
    runner = new TaskRunner(renderer, params);

    renderer->init(currentBuffer, scene);
    visualizer->init(currentBuffer, scene);
}

Renderer * Pineapple::getRenderer() {
    return renderer;
}

bool Pineapple::setRenderer(std::map<std::string, std::string> parameters) {
    std::map<std::string, std::string>::const_iterator end = parameters.end();

    // Make sure there is a type specified
    if (parameters.find("type") == end) {
        return false;
    }

    std::string type = parameters["type"];
    if (type == "opengl") {

    }
    else if (type == "raycast") {
        renderer = new Raycaster(parameters);
    }
    else {
        return false;
    }

    // Check for render method
    if (parameters.find("cores") != end) {
        int cores = std::stoi(parameters["cores"]);
        if (cores == 0) {
            cores = 1;
        }
        if (cores > 1024) {
            cores = 1024;
        }
        runner = new MPTaskRunner(renderer, cores);
    }
    // TODO Network based task runner
    else {
        runner = new TaskRunner(renderer);
    }

    return true;
}

Scene * Pineapple::getScene() {
    return scene;
}

bool Pineapple::render() {
    Camera * c = scene->getCamera();
    int width = c->viewport.x;
    int height = c->viewport.y;

    if (width * height == 0) {
        return false;
    }

    delete currentBuffer;

    float * buffer = new float[width * height * 4];
    currentBuffer = new RenderBuffer(width, height, buffer);

    if (renderer == 0) {
        return false;
    }

    // Initialization
    renderer->init(currentBuffer, scene);

    // Run
    runner->run();

    return true;
}

void Pineapple::visualize() {
    RenderTask * dummy = new RenderTask(1, 1, 0, 0, 0);
    visualizer->render(dummy);
}

RenderBuffer * Pineapple::getRenderBuffer() {
    return currentBuffer;
}
