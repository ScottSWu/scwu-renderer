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
        /**
         * List of integrators to use.
         */
        std::vector<SurfaceIntegrator *> integrators;
        /**
         * Number of samples.
         */
        int samples;
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
         * Set the current rendering targets.
         *
         * @param buffer    The buffer to render to
         * @param scene     The scene to render
         */
        void init(RenderBuffer *, Scene *);

        /**
         * Render the task.
         *
         * @param task      Task to render
         */
        void render(RenderTask *);

        /**
         * Process a task result.
         *
         * @param task      Task to process
         */
        void process(RenderTask *);

        /**
         * Returns whether there are more tasks.
         *
         * @return      Whether or not there are more tasks
         */
        bool hasTask();

        /**
         * Returns the next task.
         *
         * @return      An unfinished task
         */
        RenderTask * getTask();
};

#endif
