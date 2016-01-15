#ifndef _Pineapple_Renderer
#define _Pineapple_Renderer

class Camera;
class RenderBuffer;
class RenderTask;
class Scene;

#include <map>
#include <queue>
#include <string>
#include <vector>

/**
 * Defines an arbitrary renderer.
 */
class Renderer {
    protected:
        /**
         * This renderer's id
         */
        int rendererId;
        /**
         * Assign this renderer an id to store in objects.
         */
        void registerRenderer();
        /**
         * The current buffer to render to.
         */
        RenderBuffer * currentBuffer;
        /**
         * The current scene to render.
         */
        Scene * currentScene;
        /**
         * The current camera to render from.
         */
        Camera * currentCamera;
        /**
         * The width of the render result.
         */
        int width;
        /**
         * The height of the render result.
         */
        int height;
        /**
         * List of tasks to distribute.
         */
        std::queue<RenderTask *> tasks;
    public:
        /**
         * Count of registered renderers
         */
        static int RENDERER_COUNT;

        /**
         * Initialize a new renderer.
         *
         * @param parameters   A map of extra parameters
         */
        Renderer(std::map<std::string, std::string>);

        /**
         * Destructor
         */
        virtual ~Renderer();

        /**
         * Set the current rendering targets.
         *
         * @param buffer    The buffer to render to
         * @param scene     The scene to render
         */
        virtual void init(RenderBuffer *, Scene *);

        /**
         * Render the task.
         *
         * @param task      Task to render
         */
        virtual void render(RenderTask *);

        /**
         * Process a task result.
         *
         * @param task      Task to process
         */
        virtual void process(RenderTask *);

        /**
         * Returns whether there are more tasks.
         *
         * @return      Whether or not there are more tasks
         */
        virtual bool hasTask();

        /**
         * Returns the next task.
         *
         * @return      An unfinished task
         */
        virtual RenderTask * getTask();

        /**
         * Returns the total number of tasks.
         *
         * @return      The total number of tasks
         */
        virtual int getTaskCount();
};

#endif
