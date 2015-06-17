#ifndef _Pineapple_Renderer_GLTextureSet
#define _Pineapple_Renderer_GLTextureSet

#include <GLFW/glfw3.h>
#include <vector>

#include "Pineapple/Renderer/GLShader.hpp"

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
         * @param filename  Image file path
         * @param format    Image format
         */
        void load(const char *, GLenum);

        /**
         * Bind this texture to the current opengl context.
         *
         * @param shader    GLShader with uniform locations
         */
        void bind(const GLShader &);
};

#endif
