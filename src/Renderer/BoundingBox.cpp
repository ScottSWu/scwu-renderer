#include <glm/glm.hpp>

#include "Pineapple/BoundingBox.hpp"

BoundingBox::BoundingBox(glm::vec3 minValue, glm::vec3 maxValue) {
    minBound = minValue;
    maxBound = maxValue;
    center = (minBound + maxBound) / 2.f;
}

bool BoundingBox::contains(glm::vec3 v) {
    return minBound.x <= v.x && minBound.y <= v.y && minBound.z <= v.z &&
        v.x <= maxBound.x && v.y <= maxBound.y && v.z <= maxBound.z;
}
