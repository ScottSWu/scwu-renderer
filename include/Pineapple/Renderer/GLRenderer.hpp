#ifndef _Pineapple_Renderer_GLRenderer
#define _Pineapple_Renderer_GLRenderer

#include <map>
#include <vector>

#include "Pineapple/Renderer.hpp"
#include "Pineapple/Renderer/GLBuffer.hpp"
#include "Pineapple/Renderer/GLShader.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Light.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/Scene.hpp"

/**
 * Defines a renderer using opengl.
 */
class GLRenderer: public Renderer {
    protected:
        /** List of built-in buffers */
        std::vector<GLBuffer> defaultBuffers;
        /** List of mesh buffers */
        std::vector<GLBuffer> buffers;
        /** List of shaders */
        std::vector<GLShader> shaders;
        /** Map of shaders */
        std::map<std::string, int> shaderFiles;

        /** Whether or not gl stuff has been initialized */
        bool init;
        /**
         * Initialize on the first call to render() for gl context.
         *
         * @param scene     The scene to initialize with
         */
        void initGL();

        /**
         * Render a GLBuffer.
         *
         * @param buffer            The buffer to render
         * @param lastShader        The index of the last shader used
         * @param mProjection       The camera projection matrix
         * @param mView             The camera view matrix
         */
        void renderBuffer(GLBuffer &, int &, glm::mat4 &, glm::mat4 &);

        /**
         * Generate vertex buffers for a list of objects and their children.
         */
        void generateBuffers(Object3d *);
    public:
        /**
         * Initialize a new OpenGL renderer.
         */
        GLRenderer();

        /**
         * Destructor
         */
        ~GLRenderer();

        /**
         * Renders an image to the current gl context.
         *
         * @param imageBuffer   Dummy variable for compatibility
         * @param scene         Scene to render
         */
        void render(float[], Scene *);
};

#endif
