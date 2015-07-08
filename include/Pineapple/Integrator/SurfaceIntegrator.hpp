#ifndef _Pineapple_Integrator_Surface
#define _Pineapple_Integrator_Surface

#include "Pineapple/Ray.hpp"
#include "Pineapple/Scene.hpp"

#include <glm/glm.hpp>

class SurfaceIntegrator {
    public:
        /**
         * Initialize a new surface integrator.
         */
        SurfaceIntegrator();

        /**
         * Destructor
         */
        virtual ~SurfaceIntegrator();

        /**
         * Shade a ray through a scene using this integrator and return a color.
         *
         * @param ray       The ray to shade
         * @param scene     The scene to intersect
         */
        virtual glm::vec4 shade(const Ray &, Scene *);
};

#endif
