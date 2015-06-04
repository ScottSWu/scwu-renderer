#include <vector>

#include "Placeholder/Renderer.hpp"
#include "Placeholder/GLBuffer.hpp"
#include "Placeholder/GLShader.hpp"

#ifndef _Placeholder_Renderer_OpenGL
#define _Placeholder_Renderer_OpenGL

/**
    Defines a renderer using opengl.
*/
class GLRenderer : public Renderer {
    public:
        GLRenderer();

        void render(float[]);

        void renderBasic();

        // Initialize on the first call to render() for gl context
        bool init;
        void initGL();

        // Shader used
        // TODO Multiple shaders, link buffers to different shaders as needed
        GLShader shader;
        // Buffers made from meshes
        std::vector<GLBuffer> buffers;
};

#endif
