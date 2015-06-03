#include <stdio.h>

#include "Pineapple/GLProgram.hpp"

GLProgram::GLProgram(std::string vertFile, std::string fragFile) {
    vertexId = glCreateShader(GL_VERTEX_SHADER);
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
}
