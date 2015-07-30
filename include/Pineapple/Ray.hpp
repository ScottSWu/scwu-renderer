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
         * @param near          The near limit of the ray (default 0)
         * @param far           The far limit of the ray (default infinity)
         * @param strength      The strength of the ray
         */
        Ray(int inDepth, glm::vec3 inOrigin, glm::vec3 inDirection, float inNear = 0.f, float inFar =
                std::numeric_limits<float>::infinity(), float inStrength = 1.f);
        /**
         * Initialize a new ray.
         *
         * @param depth         Ray depth count
         * @param origin        Ray origin point
         * @param direction     Ray direction
         * @param near          The near limit of the ray (default 0)
         * @param far           The far limit of the ray (default infinity)
         * @param strength      The strength of the ray
         */
        Ray(int inDepth, glm::vec4 inOrigin, glm::vec4 inDirection, float inNear = 0.f, float inFar =
                std::numeric_limits<float>::infinity(), float inStrength = 1.f);

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
        float strength;
};

#endif
