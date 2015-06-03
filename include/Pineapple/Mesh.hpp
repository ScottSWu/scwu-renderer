#include <vector>
#include <glm/glm.hpp>

#ifndef _Pineapple_Object_Mesh
#define _Pineapple_Object_Mesh

class Mesh {
    public:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> vertexNormals;
        std::vector<glm::ivec3> faces;
        std::vector<glm::vec3> faceNormals;
};

#endif
