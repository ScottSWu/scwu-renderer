#include <glm/glm.hpp>

#include "Pineapple/Shape/Vertex.hpp"

#ifndef _Pineapple_Shape_Triangle
#define _Pineapple_Shape_Triangle

class Triangle {
    public:
        /**
         * Initialize a new triangle with three vertices.
         *
         * @param v0    The first vertex
         * @param v1    The second vertex
         * @param v2    The third vertex
         */
        Triangle(Vertex v0, Vertex v1, Vertex v2);

        /** The first vertex in the triangle */
        Vertex vertex0;
        /** The second vertex in the triangle */
        Vertex vertex1;
        /** The third vertex in the triangle *
        Vertex vertex2;

        /** Triangle normal */
        glm::vec3 normal;

        /**
         * Compute the normalized triangle normal in a counter-clockwise fashion.
         * n = normalize((v0 - v1) x (v2 - v1))
         */
        void computeNormal();
};

#endif
