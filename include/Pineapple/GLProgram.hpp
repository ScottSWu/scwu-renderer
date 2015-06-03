#ifndef _Pineapple_Object_GLProgram
#define _Pineapple_Object_GLProgram

class GLProgram {
    public:
        GLuint vertexId, fragmentId;

        GLProgram(std::string, std::string);
};

#endif
