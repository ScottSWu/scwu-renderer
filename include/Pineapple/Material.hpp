#ifndef _Pineapple_Material
#define _Pineapple_Material

class Intersection;
class Ray;
class Scene;

#include <FreeImage.h>
#include <glm/glm.hpp>

#include <map>
#include <math.h>
#include <stdio.h>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include "Pineapple/Util/FastStack.hpp"

class Material {
    protected:
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
        glm::vec4 getPixel(FIBITMAP *, int, int, glm::ivec2, const glm::ivec2 &);

        /**
         * Parse a color from a space separated string of values.
         *
         * @param string    The string to parse from
         * @return      The parsed color
         */
        static glm::vec4 getColor(std::string);

        /**
         * Reflect a direction about a normal.
         *
         * @param direction     The incoming direction
         * @param normal        The surface normal
         * @return      The reflected direction
         */
        static glm::vec4 reflect(glm::vec4, glm::vec4);
        /**
         * Refract a direction about a normal (including internal reflection).
         *
         * @param direction     The incoming direction
         * @param normal        The surface normal
         * @param ior           The index of refraction
         * @return      The refracted direction
         */
        static glm::vec4 refract(glm::vec4, glm::vec4, float);
    public:
        /**
         * Initialize a new material.
         *
         * @param parameters    A list of extra properties
         */
        Material(std::map<std::string, std::string> parameters = std::map<std::string, std::string>());

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
         * Color.
         */
        glm::vec4 maskColor;

        /**
         * Whether or not this material has a texture.
         */
        bool hasTexture;
        /**
         * Whether or not this material has a color.
         */
        bool hasColor;

        /**
         * Get a material based on a string type.
         *
         * @param type          The type of the material
         * @param parameters    The parameters to pass to the material constructor
         * @return          The material specified by the type
         */
        static Material * getMaterial(std::string, std::map<std::string, std::string>);

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
        virtual glm::vec4 sampleTexture(int texture, const glm::vec2 & uv, const glm::ivec2 & edge = glm::ivec2());

        /**
         * Sample a color from this material from an intersection result.
         *
         * @param rays      The stack of rays being processed
         * @param ray       The current intersected ray
         * @param result    The intersection result
         * @param scene     The intersected scene
         * @return      The sampled color
         */
        virtual glm::vec4 sampleColor(FastStack<Ray> & rays, const Ray ray, const Intersection & result, Scene * scene);
};

#endif
