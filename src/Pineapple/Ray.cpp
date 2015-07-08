#include "Pineapple/Ray.hpp"

Ray::Ray(glm::vec3 inOrigin, glm::vec3 inDirection, float inNear, float inFar) :
        origin(inOrigin), direction(glm::normalize(inDirection)), limits(inNear, inFar) {

}
