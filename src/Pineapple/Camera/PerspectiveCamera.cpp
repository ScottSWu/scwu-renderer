#include "Pineapple/Camera/PerspectiveCamera.hpp"

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
    return glm::perspective(fov * PAC_PI / 180.f, ratio, planes.x, planes.y);
}

Ray PerspectiveCamera::getRay(float x, float y) {
    // TODO Check to make sure this is correct
    float htany = tan(fov * 0.5f * PAC_PI / 180.f);
    float htanx = htany * (float) viewport.x / (float) viewport.y;

    float nx = (2.f * x - 1.f) * htanx;
    float ny = (2.f * y - 1.f) * htany;

    glm::vec3 forward = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.f, 1.f, 0.f)));
    glm::vec3 up = glm::normalize(glm::cross(right, forward));

    glm::vec3 direction = forward + nx * right + ny * up;

    Ray res(0, position, direction);
    return res;
}
