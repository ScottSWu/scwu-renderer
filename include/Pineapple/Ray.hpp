#ifndef _Pineapple_Ray
#define _Pineapple_Ray

#include <glm/glm.hpp>

#include <limits>

class Ray {
    public:
        /**
         * Initialize a new ray.
         *
         * @param depth         Ray depth count
         * @param origin        Ray origin point
         * @param direction     Ray direction
         * @param strength      The strength of the ray
         * @param near          The near limit of the ray (default 0)
         * @param far           The far limit of the ray (default infinity)
         */
        Ray(int inDepth = 0, glm::vec3 inOrigin = glm::vec3(0.f, 0.f, 0.f),
                glm::vec3 inDirection = glm::vec3(0.f, 0.f, 1.f), glm::vec4 inStrength = glm::vec4(1.f), float inNear =
                        0.f, float inFar = std::numeric_limits<float>::infinity());
        /**
         * Initialize a new ray.
         *
         * @param depth         Ray depth count
         * @param origin        Ray origin point
         * @param direction     Ray direction
         * @param strength      The strength of the ray
         * @param near          The near limit of the ray (default 0)
         * @param far           The far limit of the ray (default infinity)
         */
        Ray(int inDepth, glm::vec4 inOrigin, glm::vec4 inDirection, glm::vec4 inStrength = glm::vec4(1.f),
                float inNear = 0.f, float inFar = std::numeric_limits<float>::infinity());

        /**
         * Ray depth. Check this again max depth.
         */
        int depth;
        /**
         * Ray origin.
         */
        glm::vec4 origin;
        glm::vec3 origin3;
        /**
         * Ray direction.
         */
        glm::vec4 direction;
        glm::vec3 direction3;
        /**
         * Ray near and far limits.
         */
        glm::vec2 limits;
        /**
         * Ray strength
         */
        glm::vec4 strength;
};

#endif
