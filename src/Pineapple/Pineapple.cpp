#include "Pineapple/Pineapple.hpp"

#include "Pineapple/Camera.hpp"
#include "Pineapple/Light.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/Renderer.hpp"
#include "Pineapple/Renderer/GLRenderer.hpp"
#include "Pineapple/Renderer/Raycaster.hpp"
#include "Pineapple/Scene.hpp"

Pineapple::Pineapple() {
    std::map<std::string, std::string> params;
    renderer = new Renderer(params);
    visualizer = new GLRenderer(params);
    scene = new Scene();
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

    return true;
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
