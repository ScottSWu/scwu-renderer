#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Pineapple/Camera/PerspectiveCamera.hpp"
#include "Pineapple/Camera.hpp"

PerspectiveCamera::PerspectiveCamera(int width, int height, float near, float far, float inFov) :
        Camera(width, height, near, far) {
    fov = inFov;
}

PerspectiveCamera::PerspectiveCamera(float inFov) :
        Camera() {
    fov = inFov;
}

glm::mat4 PerspectiveCamera::computeProjectionMatrix() {
    float ratio = (float) viewport.x / (float) viewport.y;
    return glm::perspective(fov, ratio, planes.x, planes.y);
}
