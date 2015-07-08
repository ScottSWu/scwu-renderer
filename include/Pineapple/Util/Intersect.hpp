#ifndef _Pineapple_Util_Intersect
#define _Pineapple_Util_Intersect

#include <glm/glm.hpp>

#include <math.h>

class Ray;

/**
 * A collection of intersection functions.
 */

/**
 * Intersect a ray with a triangle.
 *
 * @param result        The barycentric coordinates and distance
 * @param ray           The intersecting ray
 * @param v0, v1, v2    The verticies of the triangle
 * @return      Whether or not the ray intersects
 */
bool IntersectTriangle(glm::vec4 & result, const Ray & ray, const glm::vec4 & v0,
        const glm::vec4 & v1, const glm::vec4 & v2);

#endif
