#include "Pineapple/Light/DirectionalLight.hpp"

#include "Pineapple/Intersection.hpp"
#include "Pineapple/Ray.hpp"
#include "Pineapple/Scene.hpp"

DirectionalLight::DirectionalLight(glm::vec4 inPosition, glm::vec4 inColor) :
        Light(inPosition, inColor, Light::TYPE_DIRECTIONAL) {

}

DirectionalLight::~DirectionalLight() {

}

glm::vec4 DirectionalLight::getFactor(Scene * scene, glm::vec4 p, glm::vec4 n) {
    // Test shadow
    glm::vec4 dir = position;
    Ray shadow(0, p, dir, PAC_EPSILON);
    std::vector<Intersection> temp;
    if (scene->getRoot()->intersect(temp, shadow, true, 1) > 0) {
        return glm::vec4(0.f, 0.f, 0.f, 0.f);
    }
    else {
        glm::vec4 dir = position;
        float factor = glm::max(glm::dot(glm::normalize(dir), n), 0.f);
        return factor * color;
    }
}
