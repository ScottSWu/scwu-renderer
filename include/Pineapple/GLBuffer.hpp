#include <GLFW/glfw3.h>

#include "Pineapple/Mesh.hpp"

#ifndef _Pineapple_Object_GLBuffer
#define _Pineapple_Object_GLBuffer

class GLBuffer {
    protected:
        Mesh parent;
    public:
        GLBuffer(const Mesh &);

        GLsizei indexSize;
        GLuint indexBuffer;
        GLuint positionBuffer, normalBuffer;

        void render();
};

#endif
