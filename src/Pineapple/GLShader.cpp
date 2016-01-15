#include "Pineapple/Renderer/GLShader.hpp"

GLShader::GLShader() :
        programId(0), vertexId(0), fragmentId(0), vViewportId(0), vCameraPositionId(0), vCameraDirectionId(0), mProjectionViewId(
                0), mProjectionId(0), mViewId(0), mTransformId(0), mTransformITId(0), iLightCountId(0) {
}

void GLShader::load(std::string vertexFile, std::string fragmentFile) {
    printf("Loading shaders v:\'%s\', f:\'%s\'\n", vertexFile.c_str(), fragmentFile.c_str());

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexCode, fragmentCode;
    
    // Read code
    std::ifstream fin;
    std::stringstream buffer;
    
    fin.clear();
    fin.open(vertexFile.c_str());

    if (fin.is_open()) {
        buffer << fin.rdbuf();
        vertexCode = buffer.str();
        fin.close();
    }
    else {
        fin.close();
        printf("\tFailed to read vertex shader.\n");
        return;
    }
    
    buffer.str(std::string());

    fin.clear();
    fin.open(fragmentFile.c_str());
    if (fin.is_open()) {
        buffer << fin.rdbuf();
        fragmentCode = buffer.str();
        fin.close();
    }
    else {
        fin.close();
        printf("\tFailed to read fragment shader.\n");
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
    if (messageSize > 1) {
        std::vector<char> message(messageSize + 1);
        glGetShaderInfoLog(vertexId, messageSize, NULL, &message[0]);
        printf("\t%s\n", &message[0]);
    }
    
    // Compile fragment shader
    codePointer = fragmentCode.c_str();
    glShaderSource(fragmentId, 1, &codePointer, NULL);
    glCompileShader(fragmentId);
    
    glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentId, GL_INFO_LOG_LENGTH, &messageSize);
    if (messageSize > 1) {
        std::vector<char> message(messageSize + 1);
        glGetShaderInfoLog(fragmentId, messageSize, NULL, &message[0]);
        printf("\t%s\n", &message[0]);
    }
    
    // Create program and attach shaders
    programId = glCreateProgram();
    glAttachShader(programId, vertexId);
    glAttachShader(programId, fragmentId);
    glLinkProgram(programId);
    
    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &messageSize);
    if (messageSize > 0) {
        std::vector<char> message(programId + 1);
        glGetProgramInfoLog(programId, messageSize, NULL, &message[0]);
        printf("\t%s\n", &message[0]);
    }
    
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    // Get uniform locations
    vViewportId = glGetUniformLocation(programId, "vViewport");
    vCameraPositionId = glGetUniformLocation(programId, "vCameraPosition");
    vCameraDirectionId = glGetUniformLocation(programId, "vCameraDirection");
    mProjectionViewId = glGetUniformLocation(programId, "mProjectionView");
    mProjectionId = glGetUniformLocation(programId, "mProjection");
    mViewId = glGetUniformLocation(programId, "mView");
    mTransformId = glGetUniformLocation(programId, "mTransform");
    mTransformITId = glGetUniformLocation(programId, "mTransformIT");
    for (char c = '0', i = 0; i < 8; i++, c++) {
        sTextureId[i] = (glGetUniformLocation(programId, "sTexture" + c));
    }
    iLightCountId = glGetUniformLocation(programId, "iLightCount");
    vLightPositionId = glGetUniformLocation(programId, "vLightPosition");
    vLightColorId = glGetUniformLocation(programId, "vLightColor");

    printf("\tDone\n");
}

void GLShader::bind() {
    glUseProgram(programId);
}

void GLShader::unbind() {
    glUseProgram(-1);
}

GLint GLShader::getUniformLocation(const char * name) {
    return glGetUniformLocation(programId, name);
}
