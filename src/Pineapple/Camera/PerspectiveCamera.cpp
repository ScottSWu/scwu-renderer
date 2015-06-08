#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Pineapple/Camera/PerspectiveCamera.hpp"

glm::mat4 Camera::computePerspectiveMatrix() {
    float ratio = (float) viewport.x / (float) viewport.y;
    return glm::perspective(fov, ratio, planes.x, planes.y);
}
