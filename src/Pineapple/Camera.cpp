#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include <stdio.h>

#include "Pineapple/Camera.hpp"

#define PI 3.141592653f

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

void Camera::setViewport(int width, int height) {
    viewport = glm::ivec2(width, height);
}

void Camera::setPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
}

void Camera::setTarget(float x, float y, float z) {
    target = glm::vec3(x, y, z);
}

void Camera::translate(float mx, float my) {
    float factor = 1.f / 100.f;
    mx *= -factor;
    my *= factor;

    glm::vec3 diff = target - position;
    glm::vec3 right = glm::normalize(glm::cross(diff, glm::vec3(0.f, 1.f, 0.f)));
    glm::vec3 up = glm::normalize(glm::cross(right, diff));

    diff = right * mx + up * my;
    position += diff;
    target += diff;
}

void Camera::rotate(float mx, float my) {
    float factor = 1.f / 200.f;
    mx *= factor;
    my *= factor;

    glm::vec3 diff = position - target;
    float theta = atan2(diff.z, diff.x) + mx;
    float rxz = sqrt(diff.x * diff.x + diff.z * diff.z);
    float phi = atan2(diff.y, rxz) + my;
    float r = glm::length(diff);

    if (phi > PI / 2.f - 0.01f) {
        phi = PI / 2.f - 0.01f;
    }
    if (phi < -PI / 2.f + 0.01f) {
        phi = -PI / 2.f + 0.01f;
    }

    diff.y = r * sin(phi);
    diff.x = r * cos(phi) * cos(theta);
    diff.z = r * cos(phi) * sin(theta);
    position = target + diff;
}

void Camera::zoom(float mx, float my) {
    float factor = 1.f / 10.f;
    float mz = (mx + my) * factor;

    glm::vec3 diff = (position - target) * (1.f - mz);

    position = target + diff;
}

void Camera::tilt(float mx, float my) {
    
}
