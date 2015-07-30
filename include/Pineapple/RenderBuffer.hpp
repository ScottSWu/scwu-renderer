#ifndef _Pineapple_RenderBuffer
#define _Pineapple_RenderBuffer

class RenderBuffer {
    public:
        /**
         * Initialize a new render buffer.
         *
         * @param width     The width of the buffer
         * @param height    The height of the buffer
         * @param buffer    A pointer to the buffer itself
         */
        RenderBuffer(int inWidth = 0, int inHeight = 0, float * inBuffer = new float[0]);

        /**
         * Destructor.
         */
        ~RenderBuffer();

        /**
         * The width of the image buffer.
         */
        int width;
        /**
         * The height of the image buffer.
         */
        int height;
        /**
         * The render image buffer.
         */
        float * buffer;
};

#endif
