#ifndef _Pineapple_Camera_Orthographic
#define _Pineapple_Camera_Orthographic

#include <glm/glm.hpp>

#include "Pineapple/Camera.hpp"

class OrthographicCamera: public Camera {
    public:
        /**
         * Initialize a new orthographic camera.
         */
        OrthographicCamera();

        /** Orthographic view bounds */
        glm::vec4 bounds;

        /**
         * Compute the orthographic projection matrix to transform into normalized space.
         *
         * @return     4x4 projection matrix
         */
        glm::mat4 computeProjectionMatrix();
};

#endif
