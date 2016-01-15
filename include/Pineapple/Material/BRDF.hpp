#ifndef _Pineapple_Material_BRDF
#define _Pineapple_Material_BRDF

#include "Pineapple/Material.hpp"

#include <glm/glm.hpp>

#include <stack>
#include <string>
#include "Pineapple/Util/FastStack.hpp"
#include "Pineapple/Util/Sampler.hpp"

#include "Pineapple/Globals.hpp"

class BRDF: public Material {
    protected:
        /**
         * Diffuse color of the material.
         */
        glm::vec4 diffuseColor;
        /**
         * Emissive color of the material.
         */
        glm::vec4 emissiveColor;
        /**
         * Emissive intensity of the material, or negative if not emissive.
         */
        float emissiveIntensity;
        /**
         * Probability of sampling emissive light. Negative if not emissive.
         */
        float emissiveProbability;
        /**
         * Max recursion depth.
         */
        int maxDepth;
    public:
        /**
         * Initialize a new BRDF.
         */
        BRDF(std::map<std::string, std::string> parameters = std::map<std::string, std::string>());

        /**
         * Destructor.
         */
        ~BRDF();

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
