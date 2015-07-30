#include "Pineapple/Ray.hpp"

Ray::Ray(int inDepth, glm::vec3 inOrigin, glm::vec3 inDirection, float inNear, float inFar, float inStrength) :
        depth(inDepth), origin(glm::vec4(inOrigin, 1.f)), origin3(glm::vec3(origin)), direction(
                glm::vec4(glm::normalize(inDirection), 0.f)), direction3(glm::vec3(direction)), limits(inNear, inFar), strength(
                inStrength) {

}

Ray::Ray(int inDepth, glm::vec4 inOrigin, glm::vec4 inDirection, float inNear, float inFar, float inStrength) :
        depth(inDepth), origin(inOrigin), origin3(glm::vec3(origin)), direction(glm::normalize(inDirection)), direction3(
                glm::vec3(direction)), limits(inNear, inFar), strength(inStrength) {

}
