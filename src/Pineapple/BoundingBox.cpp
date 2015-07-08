#include "Pineapple/BoundingBox.hpp"

#include "Pineapple/Ray.hpp"

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

/**
 * Create a new axis aligned bounding box determined by the lower and upper corners and compute the center.
 * The components of the lower corner must all be less than the corresponding uppper corner components.
 *
 * @param minValue     The lower corner
 * @param maxValue     The upper corner
 */
BoundingBox::BoundingBox(glm::vec3 minValue, glm::vec3 maxValue) {
    minBound = minValue;
    maxBound = maxValue;
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
    glm::vec3 t1 = (minBound - r.origin) / r.direction;
    glm::vec3 t2 = (maxBound - r.origin) / r.direction;

    float tmin = min(t1.x, t2.x);
    float tmax = max(t1.x, t2.x);

    tmin = max(tmin, min(min(t1.y, t2.y), tmax));
    tmax = min(tmax, max(max(t1.y, t2.y), tmin));

    tmin = max(tmin, min(min(t1.z, t2.z), tmax));
    tmax = min(tmax, max(max(t1.z, t2.z), tmin));

    return tmax > max(tmin, 0.f);
}
