#include <GLFW/glfw3.h>

#include "Placeholder/Mesh.hpp"

#ifndef _Placeholder_Object_GLBuffer
#define _Placeholder_Object_GLBuffer

/**
    Defines vertex arrays and buffers for a mesh.
*/
class GLBuffer {
    protected:
        Mesh parent;
    public:
        GLBuffer(const Mesh &);

        // Drawing mode, e.g. GL_LINES or GL_TRIANGLES
        GLenum mode;
        // Number of indices in the buffer
        GLsizei indexSize;
        // Index buffer location
        GLuint indexBuffer;
        // Attribute buffer locations
        GLuint positionBuffer, normalBuffer;

        void render();
};

#endif
