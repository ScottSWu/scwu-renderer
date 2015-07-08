#ifndef _Pineapple_Integrator_Surface_Depth
#define _Pineapple_Integrator_Surface_Depth

#include "Pineapple/Integrator/SurfaceIntegrator.hpp"

class Ray;
class Scene;

#include <vector>
#include <math.h>

class SurfaceDepthIntegrator: public SurfaceIntegrator {
    public:
        /**
         * Initialize a new surface integrator.
         */
        SurfaceDepthIntegrator();

        /**
         * Destructor.
         */
        ~SurfaceDepthIntegrator();

        /**
         * Shade a ray through a scene using this integrator and return a color.
         *
         * @param ray       The ray to shade
         * @param scene     The scene to intersect
         */
        glm::vec4 shade(const Ray &, Scene *);
};

#endif
