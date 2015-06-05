#include <GLFW/glfw3.h>
#include <string>

#ifndef _Pineapple_Object_GLShader
#define _Pineapple_Object_GLShader

/**
    Defines shader programs and their uniforms.
*/
class GLShader {
    protected:
        // Shader program locations
        GLuint programId, vertexId, fragmentId;
    public:
        GLShader();

        void load(std::string, std::string);
        void bind();
        void unbind();

        // Uniform locations for matrices
        GLuint mViewProjectionId, mTransformId, mTransformITId;
};

#endif
