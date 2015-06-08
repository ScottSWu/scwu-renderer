#include <vector>

#include "Pineapple/Object3d.hpp"

Object3d::Object3d() {
    visible = true;
    updated = false;
    wireframe = false;
}

void Object3d::addChild(Object3d object) {
    children.push_back(object);
}

void Object3d::removeChild(Object3d object) {
    children.erase(std::remove(children.begin(), children.end(), object), children.end());
}
