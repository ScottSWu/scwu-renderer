#include <glm/glm.hpp>

#ifndef _Pineapple_Light
#define _Pineapple_Light

class Light: Object3d {
    public:
        /** Ambient lighting */
        glm::vec4 ambient;
        /** Diffuse lighting */
        glm::vec4 diffuse;
        /** Specular lighting */
        glm::vec4 specular;
        /** Specular intensity */
        float intensity;
        /** Light direction */
        glm::vec4 direction;
};

#endif
