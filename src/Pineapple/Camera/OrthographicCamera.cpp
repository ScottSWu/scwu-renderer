#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Pineapple/Camera.hpp"
#include "Pineapple/Camera/OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera() :
        Camera() {

}

glm::mat4 OrthographicCamera::computeProjectionMatrix() {
    return glm::ortho(bounds.x, bounds.y, bounds.z, bounds.w, planes.x, planes.y);
}
