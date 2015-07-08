#include "Pineapple/Object3d.hpp"

#include "Pineapple/Intersection.hpp"
#include "Pineapple/Ray.hpp"

Object3d::Object3d() {
    visible = true;
    updated = false;
    wireframe = false;
}

Object3d::~Object3d() {

}

void Object3d::computeTransform(glm::mat4 parentTransform) {
    worldTransform = parentTransform * transform;
    worldTransformIT = glm::inverseTranspose(worldTransform);
    
    for (int i = 0, l = children.size(); i < l; i++) {
        children[i]->computeTransform(worldTransform);
    }
}

void Object3d::addChild(Object3d * object) {
    children.push_back(object);
}

void Object3d::removeChild(Object3d * object) {
    //children.erase(std::remove(children.begin(), children.end(), object), children.end());
    // TODO Implement custom object3d == operator
}

int Object3d::intersect(std::vector<Intersection> & results, const Ray & ray, bool recursive, int limit) {
    if (recursive) {
        for (int i = 0; i < children.size(); i++) {
            children[i]->intersect(results, ray, recursive, limit);
        }
    }
}
