#include <glm/glm.hpp>

#ifndef _Placeholder_Object_BoundingBox
#define _Placeholder_Object_BoundingBox

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
