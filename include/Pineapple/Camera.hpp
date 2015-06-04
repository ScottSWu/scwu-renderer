#include <glm/glm.hpp>

#ifndef _Pineapple_Camera
#define _Pineapple_Camera

class Camera {
    private:
        void initDefault();
    public:
        Camera();
        Camera(glm::ivec2);
        Camera(glm::ivec2, glm::vec3);

        float fov;
        glm::ivec2 viewport;
        glm::vec2 planes;

        glm::vec3 position;
        glm::vec3 target;
        glm::vec3 up;
        glm::vec3 orientation;

        glm::mat4 computeCameraMatrix();
        glm::mat4 computePerspectiveMatrix();
        glm::mat4 computeViewportMatrix();
};

#endif
