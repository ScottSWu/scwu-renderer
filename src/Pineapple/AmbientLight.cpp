#include "Pineapple/Light/AmbientLight.hpp"

AmbientLight::AmbientLight(glm::vec4 inColor) :
        Light(glm::vec4(0.f, 0.f, 0.f, 1.f), inColor, Light::TYPE_AMBIENT) {

}

AmbientLight::~AmbientLight() {

}

glm::vec4 AmbientLight::getFactor(Scene * scene, glm::vec4 position, glm::vec4 normal) {
    return glm::vec4(1.f, 1.f, 1.f, 1.f);
}
