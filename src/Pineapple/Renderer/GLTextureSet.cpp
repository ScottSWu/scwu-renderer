#include "Pineapple/Renderer/GLTextureSet.hpp"

GLTextureSet::GLTextureSet() {

}

void GLTextureSet::load(FIBITMAP * image, GLenum format) {
    // Get image data
    BYTE * data = FreeImage_GetBits(image);
    int width = FreeImage_GetWidth(image);
    int height = FreeImage_GetHeight(image);

    if ((data == 0) || (width == 0) || (height == 0)) {
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

    textures.push_back(newTexture);
}

void GLTextureSet::bind(const GLShader & shader) {
    for (int i = 0; i < 8 && i < textures.size(); i++) {
        glUniform1i(shader.sTextureId[i], i);
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }
}
