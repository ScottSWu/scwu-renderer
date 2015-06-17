#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "FreeImage.h"

#include <stdio.h>

#include "Pineapple/Renderer/GLTextureSet.hpp"

GLTextureSet::GLTextureSet() {

}

void GLTextureSet::load(const char * filename, GLenum format) {
    printf("Loading texture \'%s\'\n", filename);

    FREE_IMAGE_FORMAT imageFormat = FIF_UNKNOWN;
    FIBITMAP * image(0);
    BYTE * data(0);
    int width = 0;
    int height = 0;

    // Get image format
    imageFormat = FreeImage_GetFileType(filename, 0);
    if (imageFormat == FIF_UNKNOWN) {
        imageFormat = FreeImage_GetFIFFromFilename(filename);
    }
    if (imageFormat == FIF_UNKNOWN) { // Give up
        printf("\tUnknown image format\n");
        return;
    }

    if (FreeImage_FIFSupportsReading(imageFormat)) {
        image = FreeImage_Load(imageFormat, filename);
    }
    else {
        printf("\tUnsupported image format\n");
    }
    if (!image) {
        printf("\tCould not load file\n");
        return;
    }

    // Get image data
    data = FreeImage_GetBits(image);
    width = FreeImage_GetWidth(image);
    height = FreeImage_GetHeight(image);

    if ((data == 0) || (width == 0) || (height == 0)) {
        FreeImage_Unload(image);
        printf("\tFailed to read file\n");
        return;
    }

    // Generate texture
    GLuint newTexture;
    glGenTextures(1, &newTexture);
    glBindTexture(GL_TEXTURE_2D, newTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    printf("\tDone\n");
    textures.push_back(newTexture);

    // Free FreeImage image
    FreeImage_Unload(image);
}

void GLTextureSet::bind(const GLShader & shader) {
    glUniform1i(shader.sTexture0Id, 0);
    glUniform1i(shader.sTexture1Id, 1);
    glUniform1i(shader.sTexture2Id, 2);
    glUniform1i(shader.sTexture3Id, 3);
    glUniform1i(shader.sTexture4Id, 4);
    glUniform1i(shader.sTexture5Id, 5);
    glUniform1i(shader.sTexture6Id, 6);
    glUniform1i(shader.sTexture7Id, 7);

    for (int i = 0; i < 8 && i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }
}
