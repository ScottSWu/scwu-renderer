#ifndef _Pineapple_Object_BoundingBox
#define _Pineapple_Object_BoundingBox

class Ray;

#include <glm/glm.hpp>

#include <vector>

#include "Pineapple/Globals.hpp"

/**
 * Defines an axis aligned bounding box.
 */
class BoundingBox {
    public:
        /**
         * Initialize a new bounding box with the given min/max coordinates.
         *
         * @param minValue  The minimum coordinates of the box
         * @param maxValue  The maximum coordinates of the box
         */
        BoundingBox(glm::vec3 minValue = glm::vec3(), glm::vec3 maxValue = glm::vec3());

        /**
         * Compute an axis aligned bounding box from a list of points.
         *
         * @param points    The list of points to bound
         */
        BoundingBox(std::vector<glm::vec3>);

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

        /**
         * Return all 8 corners of the bounding box.
         *
         * @param t     A matrix to transform by (default identity)
         * @return      A vector of corners of the bounding box.
         */
        std::vector<glm::vec3> getCorners(glm::mat4 t = glm::mat4());
};

#endif
