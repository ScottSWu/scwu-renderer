#ifndef _Pineapple_Object_BoundingBox
#define _Pineapple_Object_BoundingBox

#include <glm/glm.hpp>

/**
 Defines an axis aligned bounding box.
 */
class BoundingBox {
    public:
        BoundingBox(glm::vec3, glm::vec3);

        glm::vec3 minBound;
        glm::vec3 center;
        glm::vec3 maxBound;

        bool contains(glm::vec3);
};

#endif