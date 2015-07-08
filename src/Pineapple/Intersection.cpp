#include <Pineapple/Intersection.hpp>

Intersection::Intersection(float inDist, Surface * inSurface, glm::uvec3 inIndex, glm::vec3 inCoord) :
        t(inDist), surface(inSurface), index(inIndex), coord(inCoord) {

}
