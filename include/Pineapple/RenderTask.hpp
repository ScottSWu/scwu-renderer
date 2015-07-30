#ifndef _Pineapple_Task_RenderTask
#define _Pineapple_Task_RenderTask

/**
 * Defines a rendering task. Use standard types only so everything can be easily serialized or something.
 */
class RenderTask {
    public:
        /**
         * Initialize a new render task.
         *
         * @param width     Width of the render task
         * @param height    Height of the render task
         * @param x         X offset of the render task
         * @param y         Y offset of the render task
         * @param samples   The number of samples to perform
         */
        RenderTask(int inWidth, int inHeight, int inX, int inY, int inSamples);

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
};

#endif
