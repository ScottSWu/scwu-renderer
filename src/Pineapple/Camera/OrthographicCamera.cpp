#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Pineapple/Camera.hpp"
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
