#ifndef _Pineapple_Integrator_Surface_Color
#define _Pineapple_Integrator_Surface_Color

#include "Pineapple/Integrator/SurfaceIntegrator.hpp"

class Ray;
class Scene;

#include <glm/glm.hpp>

class SurfaceColorIntegrator: public SurfaceIntegrator {
    public:
        /**
         * Initialize a new surface integrator.
         */
        SurfaceColorIntegrator();

        /**
         * Destructor.
         */
        ~SurfaceColorIntegrator();

        /**
         * Shade a ray through a scene using this integrator and return a color.
         *
         * @param ray       The ray to shade
         * @param scene     The scene to intersect
         */
        glm::vec4 shade(const Ray &, Scene *);
};

#endif
