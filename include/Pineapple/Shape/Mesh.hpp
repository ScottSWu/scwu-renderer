#include <glm/glm.hpp>
#include <vector>

#include "Pineapple/Object3d.hpp"

#ifndef _Pineapple_Shape_Mesh
#define _Pineapple_Shape_Mesh

/**
    Defines a triangle mesh.
*/
class Mesh : public Object3d {
    public:
        /** List of vertices */
        std::vector<Vertex> vertices;
        /** List of faces */
        std::vector<Triangle> faces;

        /**
            Compute vertex and face normals.
        */
        void computeNormals();
        /**
            Merge duplicate vertices together

            @param threshold    Distance threshold for merging
        */
        void mergeVertices(float);
};

#endif
