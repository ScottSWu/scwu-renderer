#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Placeholder/Camera.hpp"

/**
    Initialize a default camera.
*/
Camera::Camera() {
    initDefault();
}

/**
    Initialize a camera with a given viewport size.

    @param size     Viewport size
*/
Camera::Camera(glm::ivec2 size) {
    initDefault();

    viewport = size;
}

/**
    Initialize a camera with a given viewport size and position.

    @param size     Viewport size
    @param pos      Camera position
*/
Camera::Camera(glm::ivec2 size, glm::vec3 pos) {
    initDefault();

    viewport = size;
    position = position;
}

/**
    Initialize a camera with a given viewport size, position and target.

    @param size     Viewport size
    @param pos      Camera position
    @param tar      Viewing target
*/
Camera::Camera(glm::ivec2 size, glm::vec3 pos, glm::vec3 tar) {
    initDefault();

    viewport = size;
    position = position;
    target = tar;
}

void Camera::initDefault() {
    fov = 45.f;
    viewport = glm::ivec2(640, 480);
    planes = glm::vec2(0.01f, 100.f);

    position = glm::vec3(0.f, 0.f, 0.f);
    target = glm::vec3(0.f, 0.f, 1.f);
    up = glm::vec3(0.f, 1.f, 0.f);
}

/**
    Compute the camera matrix to transform into camera space.

    @return     4x4 camera transformation matrix
*/
glm::mat4 Camera::computeCameraMatrix() {
    return glm::lookAt(position, target, up);
}

/**
    Compute the perspective matrix to transform into orthographic space.

    @return     4x4 perspective matrix
*/
glm::mat4 Camera::computePerspectiveMatrix() {
    float ratio = (float) viewport.x / (float) viewport.y;
    return glm::perspective(fov, ratio, planes.x, planes.y);
}

/**
    Compute the viewport matrix to transform into screen space.

    @return     4x4 viewport matrix
*/
glm::mat4 Camera::computeViewportMatrix() {
    glm::mat4 vpm;
    vpm[0][0] = viewport.x / 2.f;
    vpm[1][1] = viewport.y / 2.f;
    vpm[0][3] = (viewport.x - 1.f) / 2.f;
    vpm[1][3] = (viewport.y - 1.f) / 2.f;

    return vpm;
}