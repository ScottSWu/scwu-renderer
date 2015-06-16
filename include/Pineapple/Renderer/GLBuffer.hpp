#ifndef _Pineapple_Object_GLBuffer
#define _Pineapple_Object_GLBuffer

#include <GLFW/glfw3.h>

#include "Pineapple/Shape/Mesh.hpp"

/**
 * Defines vertex arrays and buffers for a mesh.
 */
class GLBuffer {
    protected:
        /** Drawing mode, e.g. GL_LINES or GL_TRIANGLES */
        GLenum mode;
        /** Number of indices in the buffer */
        GLsizei indexSize;
        /** Index buffer location */
        GLuint indexBuffer;
        /** Position buffer location */
        GLuint positionBuffer;
        /** Normal buffer location */
        GLuint normalBuffer;
        /** UV buffer location */
        GLuint uvBuffer;
        /** Color buffer location */
        GLuint colorBuffer;
    public:
        /**
         * Initialize an empty GLBuffer
         */
        GLBuffer();

        /**
         * Initialize a new GLBuffer with a given mesh.
         *
         * @param mesh  The mesh to generate from
         */
        GLBuffer(Mesh *);

        /** Attached shader index */
        int shaderIndex;

        /**
         * Draw the GLBuffers to the current gl context.
         */
        void render();
};

#endif
