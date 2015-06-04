#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>

#include "Pineapple/GLShader.hpp"

GLShader::GLShader() {
    
}

void GLShader::load(std::string vertFile, std::string fragFile) {
    vertexId = glCreateShader(GL_VERTEX_SHADER);
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    
    std::string vertexCode, fragmentCode;
    
    // Read code
    std::ifstream fin;
    std::stringstream buffer;
    
    fin.open(vertFile.c_str());
    if (fin.is_open()) {
        buffer << fin.rdbuf();
        vertexCode = buffer.str();
        fin.close();
    }
    else {
        fin.close();
        printf("Failed to read vertex shader.\n");
        return;
    }
    
    buffer.str(std::string());
    
    fin.open(fragFile.c_str());
    if (fin.is_open()) {
        buffer << fin.rdbuf();
        fragmentCode = buffer.str();
        fin.close();
    }
    else {
        fin.close();
        printf("Failed to read fragment shader.\n");
        return;
    }
    
    // Compile and link information
    GLint result;
    int messageSize;
    const char * codePointer;
    
    // Compile vertex shader
    codePointer = vertexCode.c_str();
    glShaderSource(vertexId, 1, &codePointer, NULL);
    glCompileShader(vertexId);
    
    glGetShaderiv(vertexId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexId, GL_INFO_LOG_LENGTH, &messageSize);
	if (messageSize>0) {
		std::vector<char> message(messageSize+1);
		glGetShaderInfoLog(vertexId, messageSize, NULL, &message[0]);
		printf("%s\n", &message[0]);
	}
    
    // Compile fragment shader
    codePointer = fragmentCode.c_str();
    glShaderSource(fragmentId, 1, &codePointer, NULL);
    glCompileShader(fragmentId);
    
    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentId, GL_INFO_LOG_LENGTH, &messageSize);
	if (messageSize>0) {
		std::vector<char> message(messageSize+1);
		glGetShaderInfoLog(fragmentId, messageSize, NULL, &message[0]);
		printf("%s\n", &message[0]);
	}
    
    // Create program and attach shaders
    programId = glCreateProgram();
    glAttachShader(programId, vertexId);
    glAttachShader(programId, fragmentId);
    glLinkProgram(programId);
    
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &messageSize);
    if (messageSize>0) {
		std::vector<char> message(programId+1);
		glGetProgramInfoLog(programId, messageSize, NULL, &message[0]);
		printf("%s\n", &message[0]);
	}

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
    
    // Get uniform Locations
    glUseProgram(programId);
    mViewProjectionId = glGetUniformLocation(programId, "mViewProjection");
    mTransformId = glGetUniformLocation(programId, "mTransform");
    mTransformITId = glGetUniformLocation(programId, "mTransformIT");
}

void GLShader::bind() {
    glUseProgram(programId);
}

void GLShader::unbind() {
    glUseProgram(-1);
}
