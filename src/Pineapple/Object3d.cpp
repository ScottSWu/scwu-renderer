#include "Pineapple/Object3d.hpp"

#include "Pineapple/Intersection.hpp"
#include "Pineapple/Ray.hpp"

#include "glm/gtx/string_cast.hpp"

Object3d::Object3d() {
    needsUpdate = true;
    visible = true;
    wireframe = false;
}

Object3d::~Object3d() {

}

void Object3d::addChild(Object3d * object) {
    children.push_back(object);
}

void Object3d::removeChild(Object3d * object) {
    //children.erase(std::remove(children.begin(), children.end(), object), children.end());
    // TODO Implement custom object3d == operator
}

void Object3d::computeTransform(glm::mat4 parentTransform, bool parentUpdate) {
    if (parentUpdate || needsUpdate) {
        worldTransform = parentTransform * transform;
        worldTransformI = glm::inverse(worldTransform);
        worldTransformIT = glm::transpose(worldTransformI);

        needsUpdate = false;

        for (int i = 0, l = children.size(); i < l; i++) {
            children[i]->computeTransform(worldTransform, true);
        }
    }
    else {
        for (int i = 0, l = children.size(); i < l; i++) {
            children[i]->computeTransform(worldTransform, false);
        }
    }
}

BoundingBox Object3d::computeBoundingBox(bool recursive) {
    glm::vec3 minPoint, maxPoint;
    if (recursive) {
        for (int i = 0, l = children.size(); i < l; i++) {
            BoundingBox bbox = children[i]->computeBoundingBox();
            std::vector<glm::vec3> corners = bbox.getCorners(children[i]->worldTransform);
            for (int j = 0, m = corners.size(); j < m; j++) {
                minPoint = glm::min(minPoint, corners[j]);
                maxPoint = glm::max(maxPoint, corners[j]);
            }
        }
    }

    boundingBox = BoundingBox();
    totalBoundingBox = BoundingBox(minPoint, maxPoint);

    return totalBoundingBox;
}

int Object3d::intersect(std::vector<Intersection> & results, const Ray & ray, bool recursive, int limit) {
    int count = 0;
    if (totalBoundingBox.intersects(ray)) {
        if (recursive) {
            for (int i = 0; i < children.size(); i++) {
                count += children[i]->intersect(results, ray, recursive, limit);
                if (limit > 0 && count >= limit) {
                    return count;
                }
            }
        }
    }
    return count;
}
