#include <vector>

#include "Pineapple/Renderer.hpp"
#include "Pineapple/GLBuffer.hpp"
#include "Pineapple/GLShader.hpp"

#ifndef _Pineapple_Renderer_OpenGL
#define _Pineapple_Renderer_OpenGL

class GLRenderer : public Renderer {
    public:
        GLRenderer();

        void render(float[]);

        bool init;
        void initGL();
        
        GLShader shader;
        std::vector<GLBuffer> buffers;
        void renderBasic();
};

#endif
