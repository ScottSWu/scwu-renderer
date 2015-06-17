#ifndef _Pineapple_Shape_Mesh
#define _Pineapple_Shape_Mesh

#include <glm/glm.hpp>
#include <vector>

#include "Pineapple/Shape/Surface.hpp"
#include "Pineapple/Object3d.hpp"

class Triangle;

/**
 Defines a triangle mesh.
 */
class Mesh: public Surface {
    public:
        /**
         * Initialize a mesh with a given material.
         */
        Mesh(Material * inMaterial = new Material());

        /** List of positions */
        std::vector<glm::vec4> positions;
        /** List of normals */
        std::vector<glm::vec4> normals;
        /** List of UVs */
        std::vector<glm::vec2> uvs;
        /** list of colors */
        std::vector<glm::vec4> colors;
        /** List of faces */
        std::vector<glm::uvec3> faces;
        /** List of face normals */
        std::vector<glm::vec4> faceNormals;

        /** Number of vertices */
        int vertexCount;
        /** Number of faces */
        int faceCount;

        /**
         * Fill empty vectors with default data.
         */
        void fillDefault();

        /**
         * Compute vertex and face normals.
         */
        void computeNormals();
};

#endif
