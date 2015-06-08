#ifndef _Pineapple_Shape_Vertex
#define _Pineapple_Shape_Vertex

#include <glm/glm.hpp>

class Vertex {
    public:
        /** Vertex position */
        glm::vec3 position;
        /** Vertex normal */
        glm::vec3 normal;
        /** Vertex UV coordinates */
        glm::vec2 uv;
        /** Vertex color */
        glm::vec4 color;
};

#endif
