#include "Pineapple/Util/Intersect.hpp"

#include "Pineapple/Ray.hpp"

bool IntersectTriangle(glm::vec4 & result, const Ray & ray, const glm::vec4 & v0, const glm::vec4 & v1,
        const glm::vec4 & v2) {
    // Local basis
    glm::vec3 u(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
    glm::vec3 v(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
    glm::vec3 n(glm::normalize(glm::cross(u, v)));

    // Ray - plane intersection
    glm::vec3 o(glm::vec3(v0) - ray.origin3);
    float t = glm::dot(n, o) / glm::dot(n, ray.direction3);

    if (std::isnan(t) || t < 0) {
        return false;
    }
    if (t < ray.limits.x || t > ray.limits.y) {
        return false;
    }

    // Intersection point
    glm::vec3 p(ray.origin3 + ray.direction3 * t);
    // On-plane vector
    glm::vec3 l(p - glm::vec3(v0));

    // Compute combination of basis vectors
    float uu = glm::dot(u, u);
    float vv = glm::dot(v, v);
    float uv = glm::dot(u, v);

    float lu = glm::dot(l, u);
    float lv = glm::dot(l, v);

    float alpha = (uv * lv - vv * lu) / (uv * uv - uu * vv);
    float beta = (uv * lu - uu * lv) / (uv * uv - uu * vv);
    float gamma = 1.f - alpha - beta;

    if (alpha < 0 || beta < 0 || gamma < 0) {
        return false;
    }

    result.x = gamma;
    result.y = alpha;
    result.z = beta;
    result.w = t;

    return true;
}
