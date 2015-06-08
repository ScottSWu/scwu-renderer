#include <vector>

#include "Pineapple/Renderer.hpp"
#include "Pineapple/Renderer/GLBuffer.hpp"
#include "Pineapple/Renderer/GLShader.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Light.hpp"
#include "Pineapple/Object3d.hpp"

#ifndef _Pineapple_Renderer_GLRenderer
#define _Pineapple_Renderer_GLRenderer

/**
 Defines a renderer using opengl.
 */
class GLRenderer: public Renderer {
    protected:
        /** List of shaders used */
        std::vector<GLShader> shaders;
        /** List of vertex buffers */
        std::vector<GLBuffer> buffers;

        /** Whether or not gl stuff has been initialized */
        bool init;
        /**
         * Initialize on the first call to render() for gl context
         */
        void initGL();
    public:
        /**
         * Initialize a new OpenGL renderer.
         */
        GLRenderer();

        /**
         * Renders an image to the current gl context.
         *
         * @param imageBuffer   Dummy variable for compatibility
         * @param scene         Root scene object
         * @param camera        Camera to render from
         * @param lights        List of lights
         */
        void render(float[], Object3d, Camera, std::vector<Light>);
};

#endif
