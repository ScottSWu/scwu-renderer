#include "Pineapple/Pineapple.hpp"

Pineapple::Pineapple() {
    camera.viewport = glm::ivec2(640, 480);
    camera.position = glm::vec3(8.f, 4.f, 8.f);
    camera.orientation = glm::vec3(0.f, 0.f, 0.f);
}
