#include <GLFW/glfw3.h>
#include <string>

#ifndef _Pineapple_Object_GLShader
#define _Pineapple_Object_GLShader

class GLShader {
    protected:
        GLuint programId, vertexId, fragmentId;
    public:
        GLShader();
        
        void load(std::string, std::string);
        void bind();
        void unbind();
        
        GLuint mViewProjectionId, mTransformId, mTransformITId;
};

#endif
