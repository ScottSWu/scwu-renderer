#include <vector>

#include "Pineapple/BoundingBox.hpp"

#ifndef _Pineapple_Object_Object3D
#define _Pineapple_Object_Object3D

class Object3D {
    public:
        Object3D();

        bool visible;
        bool updated;
        bool wireframe;
        glm::mat4 transform;
        glm::mat4 transformTInv;
        std::vector<Object3D> children;
};

#endif
