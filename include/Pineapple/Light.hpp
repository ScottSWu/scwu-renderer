#ifndef _Pineapple_Light
#define _Pineapple_Light

#include "Pineapple/Object3d.hpp"

#include <glm/glm.hpp>

class Light {
    public:
        /** Position */
        glm::vec4 position;
        /** Light color */
        glm::vec4 color;
};

#endif
