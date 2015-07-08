#ifndef _Pineapple_Shape_Mesh
#define _Pineapple_Shape_Mesh

#include "Pineapple/Shape/Surface.hpp"
#include "Pineapple/Material.hpp"

class Intersection;
class Ray;

#include <glm/glm.hpp>
#include <vector>

/**
 * Defines a triangle mesh.
 */
class Mesh: public Surface {
    public:
        /**
         * Initialize a mesh with a given material.
         */
        Mesh(Material * inMaterial = new Material());
        /**
         * Destructor.
         */
        ~Mesh();

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
         * Fill empty vectors with default data, compute normals and bounding boxes, load materials.
         */
        void fillDefault();

        /**
         * Compute vertex and face normals.
         */
        void computeNormals();

        /**
         * Compute the bounding box of the mesh.
         */
        BoundingBox computeBoundingBox();

        /**
         * Sample a color from this mesh.
         *
         * @param index     Triangle indices on the mesh.
         * @param coord     Barycentric coordinate of the triangle.
         */
        glm::vec4 sampleColor(glm::uvec3, glm::vec3);

        /**
         * Intersect a ray with this mesh.
         *
         * @param result        A vector of intersections
         * @param ray           The ray to intersect with
         * @param recursive     Whether or not to test children as well (default false)
         * @param limit         Maximum number of intersections (default 0, no maximum)
         * @return  The number of intersections recorded
         */
        int intersect(std::vector<Intersection> & results, const Ray & ray, bool recursive = false, int limit = 0);
};

#endif
