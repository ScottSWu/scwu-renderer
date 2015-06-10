#include "Pineapple/Scene.hpp"

Camera & Scene::getCamera() {
    return camera;
}

std::vector<Object3d> & Scene::getObjects() {
    return objects;
}

std::vector<Light> & Scene::getLights() {
    return lights;
}

void Scene::setCameraViewport(int width, int height) {
    camera.viewport = glm::ivec2(width, height);
}

void Scene::setCameraPosition(float x, float y, float z) {
    camera.position = glm::vec3(x, y, z);
}

void Scene::setCameraTarget(float x, float y, float z) {
    camera.target = glm::vec3(x, y, z);
}

void Scene::addObject(const Object3d & object) {
    objects.push_back(object);
}

void Scene::removeObject(const Object3d & object) {
    // TODO Implement custom object3d == operator
}

void Scene::addLight(const Light & light) {
    lights.push_back(light);
}

void Scene::removeLight(const Light & light) {
    //lights.erase(std::remove(lights.begin(), lights.end(), light), lights.end());
    // TODO Implement custom light == operator
}
