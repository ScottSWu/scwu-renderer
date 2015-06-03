#include "Pineapple/Renderer.hpp"

#ifndef _Pineapple_Renderer_OpenGL
#define _Pineapple_Renderer_OpenGL

class GLRenderer : public Renderer {
    public:
        GLRenderer();

        void render(float[]);

        bool init;
        void renderBasic();
        void initGL();
};

#endif
