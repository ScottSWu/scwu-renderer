#ifndef _Pineapple_Camera_Perspective
#define _Pineapple_Camera_Perspective

#include "Pineapple/Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <math.h>

#include "Pineapple/Globals.hpp"

class PerspectiveCamera: public Camera {
    public:
        /**
         * Initialize a new perspective camera.
         */
        PerspectiveCamera(float inFov = 45.f);

        /**
         * Initialize a new perspective camera.
         */
        PerspectiveCamera(int width = 320, int height = 320, float near = 0.1f, float far = 0.1f, float inFov = 45.f);

        /** Field of view */
        float fov;

        /**
         * Compute the perspective projection matrix to transform into normalized space.
         *
         * @return     4x4 projection matrix
         */
        glm::mat4 computeProjectionMatrix();

        /**
         * Compute a ray originating from the camera based on normalized screen coordinates.
         *
         * @param nx    Normalized x coordinate
         * @param ny    Normalized y coordinate
         */
        Ray getRay(float, float);
};

#endif
