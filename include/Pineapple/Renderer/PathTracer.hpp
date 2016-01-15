#ifndef _Pineapple_Renderer_PathTracer
#define _Pineapple_Renderer_PathTracer

#include "Pineapple/Renderer.hpp"

class Scene;
class SurfaceIntegrator;

class PathTracer : public Renderer {
    private:
        /**
         * BRDF integrator.
         */
        SurfaceIntegrator * integrator;

        /**
         * Initial seed for random numbers.
         */
        int seed;

        /**
         * Number of rays per pixel.
         */
        int samples;

        /**
         * Total tasks initialized.
         */
        int totalTasks;
    public:
        /**
         * Initialize a new raycasting renderer.
         *
         * @param parameters   A map of extra parameters
         */
        PathTracer(std::map<std::string, std::string>);

        /**
         * Destructor
         */
        ~PathTracer();

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

        /**
         * Returns the total number of tasks.
         *
         * @return      The total number of tasks
         */
        int getTaskCount();
};

#endif
