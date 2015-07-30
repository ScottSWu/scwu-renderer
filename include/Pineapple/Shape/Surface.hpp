#ifndef _Pineapple_Shape_Surface
#define _Pineapple_Shape_Surface

#include "Pineapple/BoundingBox.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/Material.hpp"

class Intersection;
class Ray;

#include <glm/glm.hpp>

#include <vector>
#include <limits>

class Surface: public Object3d {
    public:
        /**
         * Initialize a new surface.
         *
         * @param mat   Surface material
         * @param mesh  Surface mesh
         */
        Surface(Material * inMaterial = new Material());

        /**
         * Destructor.
         */
        virtual ~Surface();

        /**
         * The material associated with the surface.
         */
        Material * material;

        /**
         * Sample a position from this surface.
         *
         * @param index     The index on the surface.
         * @param coord     Local coordinate on the surface.
         */
        virtual glm::vec4 samplePosition(const glm::uvec3 &, const glm::vec3 &);

        /**
         * Sample a normal from this surface.
         *
         * @param index     The index on the surface.
         * @param coord     Local coordinate on the surface.
         */
        virtual glm::vec4 sampleNormal(const glm::uvec3 &, const glm::vec3 &);

        /**
         * Sample a uv from this surface.
         *
         * @param index     The index on the surface.
         * @param coord     Local coordinate on the surface.
         */
        virtual glm::vec2 sampleUV(const glm::uvec3 &, const glm::vec3 &);

        /**
         * Sample a color from this surface.
         *
         * @param index     Index on the surface.
         * @param coord     Local coordinate on the surface.
         */
        virtual glm::vec4 sampleColor(const glm::uvec3 &, const glm::vec3 &);
};

#endif
