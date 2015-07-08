#ifndef _Pineapple_Renderer_GLTextureSet
#define _Pineapple_Renderer_GLTextureSet

#include "Pineapple/Renderer/GLShader.hpp"

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "FreeImage.h"

#include <stdio.h>

class GLTextureSet {
    protected:
        std::vector<GLuint> textures;
    public:
        /**
         * Initialize a new texture set.
         */
        GLTextureSet();

        /**
         * Load an image texture.
         *
         * @param filename  Image data
         * @param format    Image format
         */
        void load(FIBITMAP *, GLenum);

        /**
         * Bind this texture to the current opengl context.
         *
         * @param shader    GLShader with uniform locations
         */
        void bind(const GLShader &);
};

#endif
