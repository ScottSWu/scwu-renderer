#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Pineapple/Camera.hpp"

Camera::Camera(int width, int height, float near, float far) :
        target(0.f, 0.f, 1.f), up(0.f, 1.f, 0.f) {
    viewport.x = width;
    viewport.y = height;
    planes.x = near;
    planes.y = far;
}

Camera::~Camera() {
    
}

glm::mat4 Camera::computeCameraMatrix() {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::computeProjectionMatrix() {
    glm::mat4 res;
    return res;
}

void Camera::translate(float mx, float my) {
    
}

void Camera::rotate(float mx, float my) {
    
}

void Camera::zoom(float mx, float my) {
    
}

void Camera::tilt(float mx, float my) {
    
}
