#include <glm/glm.hpp>
#include <vector>

#include "Pineapple/Object3D.hpp"

#ifndef _Pineapple_Object_Mesh
#define _Pineapple_Object_Mesh

class Mesh : public Object3D {
    public:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> vertexNormals;
        std::vector<glm::uvec3> faces;
        std::vector<glm::vec3> faceNormals;
};

#endif
