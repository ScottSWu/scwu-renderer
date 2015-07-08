#ifndef _Pineapple_Renderer_GLRenderer
#define _Pineapple_Renderer_GLRenderer

#include "Pineapple/Renderer.hpp"

class GLBuffer;
class GLShader;
class GLUniforms;
class Mesh;
class Object3d;

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <stdio.h>

/**
 * Defines a renderer using opengl.
 */
class GLRenderer: public Renderer {
    protected:
        /** List of built-in meshes (grid, axes, background) */
        std::vector<Mesh *> defaultMeshes;
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
         * Recursively render an object.
         *
         * @param object        The object to render
         * @param lastShader    The index of the last shader used
         * @param uniforms      The uniform values
         */
        void renderObject(Object3d *, int &, GLUniforms &);

        /**
         * Render a GLBuffer.
         *
         * @param buffer        The buffer to render
         * @param lastShader    The index of the last shader used
         * @param uniforms      The uniform values
         */
        void renderBuffer(GLBuffer &, int &, GLUniforms &);

        /**
         * Generate vertex buffer arrays for a mesh
         *
         * @param mesh  The mesh to generate buffers
         */
        void generateBuffer(Mesh *);
    public:
        /**
         * Initialize a new OpenGL renderer.
         *
         * @param parameters   A map of extra parameters
         */
        GLRenderer(std::map<std::string, std::string>);

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
