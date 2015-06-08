#ifndef _Pineapple_Shape_Surface
#define _Pineapple_Shape_Surface

#include "Pineapple/Material.hpp"
#include "Pineapple/Object3d.hpp"

class Surface: Object3d {
    public:
        /**
         * Initialize a new surface.
         *
         * @param mat   Surface material
         * @param mesh  Surface mesh
         */
        Surface(const Material &);

        /** The material associated with this surface */
        Material material;
};

#endif
