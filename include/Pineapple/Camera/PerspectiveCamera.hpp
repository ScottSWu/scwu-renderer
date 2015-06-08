#ifndef _Pineapple_Camera_Perspective
#define _Pineapple_Camera_Perspective

#include <glm/glm.hpp>

#include "Pineapple/Camera.hpp"

class PerspectiveCamera: public Camera {
    public:
        /**
         * Initialize a new perspective camera.
         */
        PerspectiveCamera();

        /** Field of view */
        float fov = 45.f;

        /**
         * Compute the perspective projection matrix to transform into normalized space.
         *
         * @return     4x4 projection matrix
         */
        glm::mat4 computeProjectionMatrix();
};

#endif