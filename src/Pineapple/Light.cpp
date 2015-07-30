#include "Pineapple/Light.hpp"

Light::Light(glm::vec4 inPosition, glm::vec4 inColor, int inType) :
        position(inPosition), color(inColor), type(inType) {

}

Light::~Light() {

}

glm::vec4 Light::getFactor(Scene * scene, glm::vec4 position, glm::vec4 normal) {
    return glm::vec4(1.f, 1.f, 1.f, 1.f);
}
