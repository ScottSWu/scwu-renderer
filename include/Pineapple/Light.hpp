#ifndef _Pineapple_Light
#define _Pineapple_Light

#include <glm/glm.hpp>

#include "Pineapple/Object3d.hpp"

class Light {
    public:
        /** Position */
        glm::vec3 position;
        /** Light color */
        glm::vec4 color;
        /** Intensity */
        float intensity;
        /** Light direction */
        glm::vec4 direction;
};

#endif
