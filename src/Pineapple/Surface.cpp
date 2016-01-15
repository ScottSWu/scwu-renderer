#include "Pineapple/Shape/Surface.hpp"

Surface::Surface(Material * inMaterial) :
        Object3d() {
    material = inMaterial;
}

Surface::~Surface() {

}

glm::vec4 Surface::samplePosition(const glm::uvec3 & index, const glm::vec3 & coord) {
    return glm::vec4(0.f, 0.f, 0.f, 1.f);
}

glm::vec4 Surface::sampleNormal(const glm::uvec3 & index, const glm::vec3 & coord) {
    return glm::vec4(0.f, 1.f, 0.f, 0.f);
}

glm::vec2 Surface::sampleUV(const glm::uvec3 & index, const glm::vec3 & coord) {
    return glm::vec2(0.f, 0.f);
}

glm::vec4 Surface::sampleColor(const glm::uvec3 & index, const glm::vec3 & coord) {
    return glm::vec4(0.f, 0.f, 0.f, 0.f);
}
