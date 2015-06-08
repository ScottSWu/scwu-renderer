#ifndef _Pineapple_Object_GLShader
#define _Pineapple_Object_GLShader

#include <GLFW/glfw3.h>
#include <string>

/**
 * Defines shader programs and their uniforms.
 */
class GLShader {
    protected:
        /** Shader program location */
        GLuint programId;
        /** Vertex shader location */
        GLuint vertexId;
        /** Fragment shader location */
        GLuint fragmentId;
    public:
        /**
         * Initialize a new shader program.
         */
        GLShader();

        /**
         * Load vertex and fragment shader code by filename.
         *
         * @param vertexFile    Path to vertex code file
         * @param fragmentFile    Path to fragment code file
         */
        void load(std::string, std::string);
        /**
         * Bind this shader and its uniforms to the current gl context.
         */
        void bind();
        /**
         * Unbind this shader from the current gl context.
         */
        void unbind();
        /**
         * Get a shader uniform location by name.
         *
         * @param name  Uniform name
         * @return  Uniform location int
         */
        GLint getUniformLocation(std::string);
};

#endif
