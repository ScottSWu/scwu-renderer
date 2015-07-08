#ifndef _Pineapple_Intersection
#define _Pineapple_Intersection

class Surface;

#include "Pineapple/Shape/Surface.hpp"

#include <glm/glm.hpp>

#include <vector>

/**
 * Defines an intersection.
 */
class Intersection {
    public:
        /**
         * Initialize a new intersection record.
         *
         * @param t         The distance to the intersection (in units of the ray direction)
         * @param surface   The intersected surface
         * @param index     The intersection index
         * @param coord     The intersection coordinates (surface dependent)
         */
        Intersection(float, Surface *, glm::uvec3, glm::vec3);

        /**
         * Distance to the intersection point from the ray origin.
         */
        float t;

        /**
         * Intersected surface.
         */
        Surface * surface;

        /**
         * Intersection index.
         */
        glm::uvec3 index;

        /**
         * Intersection coordinate.
         */
        glm::vec3 coord;
};

#endif
