#include "Pineapple/Shape/Surface.hpp"

Surface::Surface(Material * inMaterial) :
        Object3d() {
    material = inMaterial;
}

Surface::~Surface() {

}

BoundingBox Surface::computeBoundingBox() {
    return bounds;
}

glm::vec4 Surface::sampleColor(glm::uvec3, glm::vec3) {
    return glm::vec4();
}
