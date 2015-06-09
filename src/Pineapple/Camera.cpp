#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Pineapple/Camera.hpp"

Camera::Camera() {
    
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
