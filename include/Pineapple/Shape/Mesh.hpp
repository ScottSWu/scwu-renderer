#ifndef _Pineapple_Shape_Mesh
#define _Pineapple_Shape_Mesh

#include <glm/glm.hpp>
#include <vector>

#include "Pineapple/Shape/Surface.hpp"
#include "Pineapple/Shape/Vertex.hpp"
#include "Pineapple/Shape/Triangle.hpp"
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

        /** List of vertices */
        std::vector<Vertex> vertices;
        /** List of faces */
        std::vector<Triangle> faces;

        /**
         * Compute vertex and face normals.
         */
        void computeNormals();
        /**
         * Merge duplicate vertices together
         *
         * @param threshold    Distance threshold for merging
         */
        void mergeVertices(float);
};

#endif
