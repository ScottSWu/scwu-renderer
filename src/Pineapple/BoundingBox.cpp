#include "Pineapple/BoundingBox.hpp"

#include "Pineapple/Ray.hpp"

BoundingBox::BoundingBox(glm::vec3 minValue, glm::vec3 maxValue) {
    minBound = minValue - PAC_EPSILON;
    maxBound = maxValue + PAC_EPSILON;
    center = (minBound + maxBound) / 2.f;
}

BoundingBox::BoundingBox(std::vector<glm::vec3> points) {
    if (points.size() > 0) {
        minBound = points[0];
        maxBound = points[0];

        for (int i = 0, l = points.size(); i < l; i++) {
            minBound = glm::min(minBound, points[i]);
            maxBound = glm::max(maxBound, points[i]);
        }
    }

    center = (minBound + maxBound) / 2.f;
}

bool BoundingBox::contains(glm::vec3 v) {
    return minBound.x <= v.x && minBound.y <= v.y && minBound.z <= v.z && v.x <= maxBound.x && v.y <= maxBound.y
            && v.z <= maxBound.z;
}

/**
 * From
 * http://tavianator.com/fast-branchless-raybounding-box-intersections-part-2-nans/
 *
 * Programming, Ray Tracing
 * Fast, Branchless Ray/Bounding Box Intersections
 * Tavian Barnes
 * May 2, 2011
 */
bool BoundingBox::intersects(Ray r) {
    glm::vec3 t1 = (minBound - r.origin3) / r.direction3;
    glm::vec3 t2 = (maxBound - r.origin3) / r.direction3;

    float tmin = glm::min(t1.x, t2.x);
    float tmax = glm::max(t1.x, t2.x);

    tmin = glm::max(tmin, glm::min(glm::min(t1.y, t2.y), tmax));
    tmax = glm::min(tmax, glm::max(glm::max(t1.y, t2.y), tmin));

    tmin = glm::max(tmin, glm::min(glm::min(t1.z, t2.z), tmax));
    tmax = glm::min(tmax, glm::max(glm::max(t1.z, t2.z), tmin));

    return tmax > glm::max(tmin, 0.f);
}

std::vector<glm::vec3> BoundingBox::getCorners(glm::mat4 t) {
    std::vector<glm::vec3> corners;

    corners.push_back(glm::vec3(t * glm::vec4(minBound.x, minBound.y, minBound.z, 1.f)));
    corners.push_back(glm::vec3(t * glm::vec4(minBound.x, minBound.y, maxBound.z, 1.f)));
    corners.push_back(glm::vec3(t * glm::vec4(minBound.x, maxBound.y, minBound.z, 1.f)));
    corners.push_back(glm::vec3(t * glm::vec4(minBound.x, maxBound.y, maxBound.z, 1.f)));
    corners.push_back(glm::vec3(t * glm::vec4(maxBound.x, minBound.y, minBound.z, 1.f)));
    corners.push_back(glm::vec3(t * glm::vec4(maxBound.x, minBound.y, maxBound.z, 1.f)));
    corners.push_back(glm::vec3(t * glm::vec4(maxBound.x, maxBound.y, minBound.z, 1.f)));
    corners.push_back(glm::vec3(t * glm::vec4(maxBound.x, maxBound.y, maxBound.z, 1.f)));

    return corners;
}
