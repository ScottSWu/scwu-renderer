#ifndef _Pineapple_Integrator_Surface_Material
#define _Pineapple_Integrator_Surface_Material

#include "Pineapple/Integrator/SurfaceIntegrator.hpp"

class Ray;
class Scene;

#include <glm/glm.hpp>

class SurfaceMaterialIntegrator: public SurfaceIntegrator {
    public:
        /**
         * Initialize a new surface integrator.
         */
        SurfaceMaterialIntegrator();

        /**
         * Destructor.
         */
        ~SurfaceMaterialIntegrator();

        /**
         * Shade a ray through a scene using this integrator and return a color.
         *
         * @param ray       The ray to shade
         * @param scene     The scene to intersect
         */
        glm::vec4 shade(const Ray &, Scene *);
};

#endif
