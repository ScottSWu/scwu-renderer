#include <glm/glm.hpp>

#ifndef _Pineapple_Camera
#define _Pineapple_Camera

/**
 * Defines a camera.
 */
class Camera {
    public:
        /**
         * Initialize a default camera.
         */
        Camera();

        // Positive viewport width and height
        glm::ivec2 viewport;

        // Camera position
        glm::vec3 position;
        // Camera lookAt target
        glm::vec3 target;
        // Camera up orientation
        glm::vec3 up;

        /**
         * Compute the camera matrix to transform into camera space.
         *
         * @return     4x4 camera transformation matrix
         */
        glm::mat4 computeCameraMatrix();
        /**
         * Compute the perspective matrix to transform into orthographic space.
         *
         * @return     4x4 perspective matrix
         */
        virtual glm::mat4 computePerspectiveMatrix();
};

#endif
