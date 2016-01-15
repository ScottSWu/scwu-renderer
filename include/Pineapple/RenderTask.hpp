#ifndef _Pineapple_Task_RenderTask
#define _Pineapple_Task_RenderTask

/**
 * Defines a rendering task. Use standard types only so everything can be easily serialized or something.
 */
class RenderTask {
    private:
        static int generateId;
    public:
        /**
         * Initialize a new render task.
         *
         * @param width     Width of the render task
         * @param height    Height of the render task
         * @param x         X offset of the render task
         * @param y         Y offset of the render task
         * @param samples   The number of samples to perform
         * @param seed      The seed for random number generation
         */
        RenderTask(int inWidth, int inHeight, int inX, int inY, int inSamples, int inSeed = 0);

        /**
         * Destructor.
         */
        ~RenderTask();

        /**
         * The width of the task.
         */
        int width;

        /**
         * The height of the task.
         */
        int height;

        /**
         * The X offset of the task.
         */
        int x;

        /**
         * The Y offset of the task.
         */
        int y;

        /**
         * The number of samples.
         */
        int samples;

        /**
         * Result data.
         */
        float * data;

        /**
         * Unique task id.
         */
        int id;

        /**
         * Task seed.
         */
        int seed;
};

#endif
