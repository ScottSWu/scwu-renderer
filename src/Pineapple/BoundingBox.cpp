#include <glm/glm.hpp>

#include "Pineapple/BoundingBox.hpp"

/**
 Create a new bounding box determined by the lower and upper corners and compute the center.
 The components of the lower corner must all be less than the corresponding uppper corner components.

 @param minValue     The lower corner
 @param maxValue     The upper corner
 */
BoundingBox::BoundingBox(glm::vec3 minValue, glm::vec3 maxValue) {
    minBound = minValue;
    maxBound = maxValue;
    center = (minBound + maxBound) / 2.f;
}

/**
 Check if a point is within this bounding box.

 @param v    The point to check
 @return     Whether or not v is within this bounding box
 */
bool BoundingBox::contains(glm::vec3 v) {
    return minBound.x <= v.x && minBound.y <= v.y && minBound.z <= v.z && v.x <= maxBound.x && v.y <= maxBound.y
            && v.z <= maxBound.z;
}
