#include <glm/glm.hpp>

#ifndef _Pineapple_Object_BoundingBox
#define _Pineapple_Object_BoundingBox

class BoundingBox {
    public:
        BoundingBox(glm::vec3, glm::vec3);

        glm::vec3 minBound;
        glm::vec3 center;
        glm::vec3 maxBound;

        bool contains(glm::vec3);
};

#endif
