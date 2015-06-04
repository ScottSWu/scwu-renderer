#include <vector>

#include "Placeholder/BoundingBox.hpp"

#ifndef _Placeholder_Object_Object3D
#define _Placeholder_Object_Object3D

/**
    Defines an object in the scene.
*/
class Object3D {
    public:
        Object3D();

        // Whether or not the object is visible
        bool visible;
        // Whether or not the object properties have been updated
        bool updated;
        // Whether or not the object is a wireframe
        bool wireframe;
        // Transformation matrix
        glm::mat4 transform;
        // Inverse transpose of the transformation matrix
        glm::mat4 transformIT;
        // List of children
        std::vector<Object3D> children;
};

#endif
