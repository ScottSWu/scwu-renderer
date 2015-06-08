#ifndef _Pineapple_Shape_Triangle
#define _Pineapple_Shape_Triangle

#include <glm/glm.hpp>

#include "Pineapple/Shape/Vertex.hpp"
#include "Pineapple/Shape/Mesh.hpp"

class Mesh;

class Triangle {
    public:
        /**
         * Initialize a new triangle with three vertices.
         *
         * @param parent    The parent mesh
         * @param v0        The first vertex
         * @param v1        The second vertex
         * @param v2        The third vertex
         */
        Triangle(Mesh *, unsigned int, unsigned int, unsigned int);

        /** Parent mesh containing this triangle */
        Mesh * parent;

        /** The first vertex in the triangle */
        unsigned int vertex0;
        /** The second vertex in the triangle */
        unsigned int vertex1;
        /** The third vertex in the triangle */
        unsigned int vertex2;

         /** Triangle normal */
        glm::vec3 normal;

        /**
         * Compute the normalized triangle normal in a counter-clockwise fashion.
         * n = normalize((v0 - v1) x (v2 - v1))
         */
        void computeNormal();

        /**
         * Return corresponding indices for each vertex.
         *
         * @return  Integer vector of indices
         */
        glm::uvec3 getIndices();
};

#endif
