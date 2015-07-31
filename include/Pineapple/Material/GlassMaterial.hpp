#ifndef _Pineapple_Material_Glass
#define _Pineapple_Material_Glass

class Intersection;
class Ray;
class Scene;

#include "Pineapple/Material.hpp"

#include <glm/glm.hpp>

#include <stack>
#include <string>
#include "Pineapple/Util/FastStack.hpp"

#include "Pineapple/Globals.hpp"

class GlassMaterial: public Material {
    protected:
        /**
         * Transmission index of refraction.
         */
        float indexOfRefraction;
        /**
         * Transmission mix
         */
        float tMix;
        /**
         * Reflection mix
         */
        float rMix;
        /**
         * Tint mix (maskColor)
         */
        float cMix;
        /**
         * Max recursion depth
         */
        int maxDepth;
        /**
         * Reflect a direction about a normal.
         *
         * @param direction     The incoming direction
         * @param normal        The surface normal
         * @return      The reflected direction
         */
        glm::vec4 reflect(glm::vec4, glm::vec4);
        /**
         * Refract a direction about a normal (including internal reflection).
         *
         * @param direction     The incoming direction
         * @param normal        The surface normal
         * @return      The refracted direction
         */
        glm::vec4 refract(glm::vec4, glm::vec4);
    public:
        /**
         * Initialize a new diffuse material.
         */
        GlassMaterial(std::map<std::string, std::string> parameters = std::map<std::string, std::string>());

        /**
         * Destructor.
         */
        ~GlassMaterial();

        /**
         * Sample a color from this material from an intersection result.
         *
         * @param rays      The stack of rays being processed
         * @param ray       The current intersected ray
         * @param result    The intersection result
         * @param scene     The intersected scene
         * @return      The sampled color
         */
        glm::vec4 sampleColor(FastStack<Ray> & rays, const Ray ray, const Intersection & result, Scene * scene);
};

#endif
