#include <glm/glm.hpp>

#ifndef _Pineapple_Camera
#define _Pineapple_Camera

/**
    Defines a camera.
*/
class Camera {
    private:
        void initDefault();
    public:
        Camera();
        Camera(glm::ivec2);
        Camera(glm::ivec2, glm::vec3);
        Camera(glm::ivec2, glm::vec3, glm::vec3);

        // Camera field of view
        float fov;
        // Positive viewport width and height
        glm::ivec2 viewport;
        // Near and far planes
        glm::vec2 planes;

        // Camera position
        glm::vec3 position;
        // Camera lookAt target
        glm::vec3 target;
        // Camera up orientation
        glm::vec3 up;
        // Camera orientation TODO combine into target instead
        glm::vec3 orientation;

        glm::mat4 computeCameraMatrix();
        glm::mat4 computePerspectiveMatrix();
        glm::mat4 computeViewportMatrix();
};

#endif
