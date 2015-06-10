#ifndef _Pineapple_Camera_Orthographic
#define _Pineapple_Camera_Orthographic

#include <glm/glm.hpp>

#include "Pineapple/Camera.hpp"

class OrthographicCamera: public Camera {
    public:
        /**
         * Initialize a  new orthogrpahic camera.
         */
        OrthographicCamera(float left = -1.f, float right = 1.f, float top = 1.f, float bottom = -1.f);

        /**
         * Initialize a new orthographic camera.
         */
        OrthographicCamera(int width = 320, int height = 320, float near = 0.1f, float far = 0.1f, float left = -1.f,
                float right = 1.f, float top = 1.f, float bottom = -1.f);

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
