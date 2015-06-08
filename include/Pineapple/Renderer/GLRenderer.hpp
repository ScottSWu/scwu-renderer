#ifndef _Pineapple_Renderer_GLRenderer
#define _Pineapple_Renderer_GLRenderer

#include <vector>

#include "Pineapple/Renderer.hpp"
#include "Pineapple/Renderer/GLBuffer.hpp"
#include "Pineapple/Renderer/GLShader.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Light.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/Scene.hpp"

/**
 Defines a renderer using opengl.
 */
class GLRenderer: public Renderer {
    protected:
        /** Shader */
        GLShader shader;
        /** List of vertex buffers */
        std::vector<GLBuffer> buffers;

        /** Uniform location for the view projection matrix */
        GLint mViewProjectionId;
        /** Uniform location for the transformation matrix */
        GLint mTransformId;
        /** Uniform location for the inverse transpose matrix */
        GLint mTransformITId;

        /** Whether or not gl stuff has been initialized */
        bool init;
        /**
         * Initialize on the first call to render() for gl context.
         *
         * @param scene     The scene to initialize with
         */
        void initGL(Scene *);
    public:
        /**
         * Initialize a new OpenGL renderer.
         */
        GLRenderer();

        /**
         * Renders an image to the current gl context.
         *
         * @param imageBuffer   Dummy variable for compatibility
         * @param scene         Scene to render
         */
        void render(float[], Scene *);
};

#endif
