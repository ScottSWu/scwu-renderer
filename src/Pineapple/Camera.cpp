#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Pineapple/Camera.hpp"

Camera::Camera() {

}

glm::mat4 Camera::computeCameraMatrix() {
    return glm::lookAt(position, target, up);
}
