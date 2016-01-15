#include "Pineapple/Light/PointLight.hpp"

#include "Pineapple/Intersection.hpp"
#include "Pineapple/Ray.hpp"
#include "Pineapple/Scene.hpp"

PointLight::PointLight(glm::vec4 inPosition, glm::vec4 inColor, float inIntensity) :
        Light(inPosition, inColor, Light::TYPE_POINT), intensity(inIntensity) {

}

PointLight::~PointLight() {

}

glm::vec4 PointLight::getFactor(Scene * scene, glm::vec4 p, glm::vec4 n) {
    // Test shadow
    glm::vec4 dir = position - p;
    Ray shadow(0, p, dir, glm::vec4(1.f), PAC_EPSILON, glm::length(dir));
    std::vector<Intersection> temp;
    if (scene->getRoot()->intersect(temp, shadow, true, 1) > 0) {
        return glm::vec4(0.f, 0.f, 0.f, 0.f);
    }
    else {
        glm::vec4 dir = position - p;
        float r = dir.length();
        float factor = intensity / (r * r) * glm::max(glm::dot(glm::normalize(dir), n), 0.f);
        return factor * color;
    }
}
