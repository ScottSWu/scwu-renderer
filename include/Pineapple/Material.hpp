#ifndef _Pineapple_Material
#define _Pineapple_Material

#include <FreeImage.h>
#include <glm/glm.hpp>

#include <map>
#include <math.h>
#include <stdio.h>
#include <string>
#include <vector>

class Material {
    private:
        /**
         * Load an image from a file.
         *
         * @param filename  The filename of the image
         */
        FIBITMAP * loadImage(const char *);

        /**
         * Get a pixel from an image.
         *
         * @param image     The image to retrieve from
         * @param width     The width of the image
         * @param height    The height of the image
         * @param coord     The pixel coordinates
         * @param edge      The edge behavior for out-of-bounds coordinates
         * @return      The color of the pixel
         */
        glm::vec4 getPixel(FIBITMAP *, int, int, glm::uvec2, glm::uvec2);
    public:
        /**
         * Initialize a new material.
         */
        Material();

        /**
         * Destructor
         */
        virtual ~Material();

        /**
         * Additional properties.
         */
        std::map<std::string, std::string> properties;

        /**
         * List of textures.
         */
        std::vector<FIBITMAP *> textures;

        /**
         * Load / reload textures.
         */
        void loadTextures();

        /**
         * Sample textures from this material.
         *
         * @param texture   The texture number to sample
         * @param uv        The uv coordinates to sample, (0, 0) being bottom-left
         * @param edge      Edge behavior for each coordinate (-1 is empty, 0 is clamp, 1 is repeat)
         * @return          The sampled color, or empty if invalid
         */
        glm::vec4 sampleTexture(int texture, glm::vec2 uv, glm::uvec2 edge = glm::uvec2());
};

#endif
