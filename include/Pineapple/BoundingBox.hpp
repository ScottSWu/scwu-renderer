#ifndef _Pineapple_Object_BoundingBox
#define _Pineapple_Object_BoundingBox

class Ray;

#include <glm/glm.hpp>

/**
 * Defines an axis aligned bounding box.
 */
class BoundingBox {
    public:
        /**
         * Initialize a new bounding box with the given min/max coordinates.
         *
         * @param minValue  The minimum coordinates of the box
         * @param maxVluae  The maximum coordinates of the box
         */
        BoundingBox(glm::vec3 minValue = glm::vec3(), glm::vec3 maxValue = glm::vec3());

        glm::vec3 minBound;
        glm::vec3 center;
        glm::vec3 maxBound;

        /**
         * Check if a point is within this bounding box.
         *
         * @param v    The point to check
         * @return     Whether or not the point is within this bounding box
         */
        bool contains(glm::vec3);

        /**
         * Check if a ray intersects this bounding box.
         *
         * @param r     The ray to check
         * @return      Whether or not the ray intersects this bounding box
         */
        bool intersects(Ray);
};

#endif
