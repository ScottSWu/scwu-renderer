#include "Pineapple/Scene.hpp"

Scene::Scene(Camera * inCamera) {
    camera = inCamera;
    root = new Object3d();
}

void Scene::setCamera(Camera * inCamera) {
    camera = inCamera;
}

void Scene::setCameraViewport(int width, int height) {
    camera->viewport = glm::ivec2(width, height);
}

void Scene::setCameraPosition(float x, float y, float z) {
    camera->position = glm::vec3(x, y, z);
}

void Scene::setCameraTarget(float x, float y, float z) {
    camera->target = glm::vec3(x, y, z);
}

Camera * Scene::getCamera() {
    return camera;
}

Object3d * Scene::getRoot() {
    return root;
}

std::vector<Object3d *> Scene::getObjects() {
    return root->children;
}

std::vector<Light *> Scene::getLights() {
    return lights;
}

void Scene::addObject(Object3d * object) {
    root->addChild(object);
}

void Scene::removeObject(Object3d * object) {
    root->removeChild(object);
}

void Scene::addLight(Light * light) {
    lights.push_back(light);
}

void Scene::removeLight(Light * light) {
    //lights.erase(std::remove(lights.begin(), lights.end(), light), lights.end());
    // TODO Implement custom light == operator
}
