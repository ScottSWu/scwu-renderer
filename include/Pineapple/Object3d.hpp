#include <glm/glm.hpp>
#include <vector>

#ifndef _Pineapple_Object3d
#define _Pineapple_Object3d

/**
 * Defines an object in the scene.
 */
class Object3d {
    protected:
        /** List of children */
        std::vector<Object3d> children;
        /** Indexed locations for multiple renderers */
        std::vector<int> rendererIndex;
    public:
        /**
         Initialize a new object.
         */
        Object3d();

        /** Whether or not the object is visible */
        bool visible;
        /** Whether or not the object properties have been updated */
        bool updated;
        /** Whether or not the object is a wireframe */
        bool wireframe;
        /** Local transformation matrix */
        glm::mat4 transform;
        /** Computed complete transformation matrix */
        glm::mat4 worldTransform;
        /** Inverse transpose of the complete transformation matrix */
        glm::mat4 worldTransformIT;

        /**
         Add a child object.

         @param object   Object to add
         */
        void addChild(Object3d);
        /**
         Remove a child object.

         @param object   Object to remove
         */
        void removeChild(Object3d);
};

#endif
