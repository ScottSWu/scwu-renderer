#include "Pineapple/Camera/OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(int width, int height, float near, float far, float left, float right, float top,
        float bottom) :
        Camera(width, height, near, far) {
    bounds.x = left;
    bounds.y = right;
    bounds.z = top;
    bounds.w = bottom;
}

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom) :
        Camera() {
    bounds.x = left;
    bounds.y = right;
    bounds.z = top;
    bounds.w = bottom;
}

glm::mat4 OrthographicCamera::computeProjectionMatrix() {
    return glm::ortho(bounds.x, bounds.y, bounds.z, bounds.w, planes.x, planes.y);
}

Ray OrthographicCamera::getRay(float x, float y) {
    float nx = (bounds.y - bounds.x) * x + bounds.x;
    float ny = (bounds.z - bounds.w) * y + bounds.w;

    glm::vec3 forward = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.f, 1.f, 0.f)));
    glm::vec3 up = glm::normalize(glm::cross(right, forward));

    glm::vec3 direction = nx * right + ny * up;

    Ray res(position + direction, forward);
    return res;
}
