#ifndef _Pineapple_Renderer_Raycaster
#define _Pineapple_Renderer_Raycaster

#include "Pineapple/Renderer.hpp"

#include <map>
#include <string>
#include <vector>

class Scene;
class SurfaceIntegrator;

class Raycaster: public Renderer {
    private:
        std::vector<SurfaceIntegrator *> integrators;
    public:
        /**
         * Initialize a new raycasting renderer.
         *
         * @param parameters   A map of extra parameters
         */
        Raycaster(std::map<std::string, std::string>);

        /**
         * Destructor
         */
        ~Raycaster();

        /**
         * Renders an image to the current gl context.
         *
         * @param imageBuffer   Render target image buffer
         * @param scene         Scene to render
         */
        void render(float[], Scene *);
};

#endif
