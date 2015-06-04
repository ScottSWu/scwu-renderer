#include <glm/glm.hpp>
#include <vector>

#include "Placeholder/Object3D.hpp"

#ifndef _Placeholder_Object_Mesh
#define _Placeholder_Object_Mesh

/**
    Defines a triangle mesh.

    TODO UVs, colors, automatic normals
*/
class Mesh : public Object3D {
    public:
        // List of vertices
        std::vector<glm::vec3> vertices;
        // List of vertex normals
        std::vector<glm::vec3> vertexNormals;
        // List of face indices
        std::vector<glm::uvec3> faces;
};

#endif
