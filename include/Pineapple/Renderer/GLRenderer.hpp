#include <vector>

#include "Pineapple/Renderer/Renderer.hpp"
#include "Pineapple/Renderer/GLBuffer.hpp"
#include "Pineapple/Renderer/GLShader.hpp"

#ifndef _Pineapple_Renderer_GLRenderer
#define _Pineapple_Renderer_GLRenderer

/**
    Defines a renderer using opengl.
*/
class GLRenderer : public Renderer {
    protected:
        /** List of shaders used */
        std::vector<GLShader> shaders;
        /** List of vertex buffers */
        std::vector<GLBuffer> buffers;
    public:
        GLRenderer();

        void render(float[], Object3d, Camera, std::vector<Light>);

        /**
            Visualize the current scene.
        */
        void visualize();

        // Initialize on the first call to render() for gl context
        bool init;
        void initGL();
};

#endif
