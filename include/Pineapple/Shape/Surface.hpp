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
         * The bounding box of the surface.
         */
        BoundingBox bounds;

        /**
         * Compute the bounding box of this surface.
         */
        virtual BoundingBox computeBoundingBox();

        /**
         * Sample a color from this surface.
         *
         * @param index     Index on the surface.
         * @param coord     Local coordinate on the surface.
         */
        virtual glm::vec4 sampleColor(glm::uvec3, glm::vec3);
};

#endif
