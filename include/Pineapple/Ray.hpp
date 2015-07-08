#ifndef _Pineapple_Ray
#define _Pineapple_Ray

#include <glm/glm.hpp>

#include <limits>

class Ray {
    public:
        /**
         * Initialize a new ray.
         *
         * @param origin        Ray origin point
         * @param direction     Ray direction
         * @param near          The near limit of the ray (default 0)
         * @param far           The far limit of the ray (default infinity)
         */
        Ray(glm::vec3 inOrigin, glm::vec3 inDirection, float inNear = 0.f, float inFar =
                std::numeric_limits<float>::infinity());

        /**
         * Ray origin.
         */
        glm::vec3 origin;
        /**
         * Ray direction.
         */
        glm::vec3 direction;
        /**
         * Ray near and far limits.
         */
        glm::vec2 limits;
};

#endif
