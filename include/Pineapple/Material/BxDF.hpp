#ifndef _Pineapple_Material_BxDF
#define _Pineapple_Material_BxDF

#include "Pineapple/Material.hpp"

#include <glm/glm.hpp>

#include <stack>
#include <string>
#include "Pineapple/Util/FastStack.hpp"
#include "Pineapple/Util/Sampler.hpp"

#include "Pineapple/Globals.hpp"

/**
 * General bidirectional distribution function
 */
class BxDF: public Material {
    protected:
        /**
         * Function type.
         */
        int type;
        /**
         * List of types
         */
        static const int TYPE_NONE = 0;
        static const int TYPE_EMISSIVE = 1;
        static const int TYPE_DIFFUSE = 2;
        static const int TYPE_GLASS = 3;
        /**
         * Associated color of the material.
         */
        glm::vec4 color;
        /**
         * Associated secondary color of the material.
         */
        glm::vec4 altColor;
        /**
         * Associated intensity of the material.
         */
        float intensity;
        /**
         * Associated secondary intensity of the material.
         */
        float altIntensity;
        /**
         * Associated attribute of the material.
         */
        float attribute;
        /**
         * Associated secondary attribute of the material.
         */
        float altAttribute;
        /**
         * Max recursion depth.
         */
        int maxDepth;
    public:
        /**
         * Initialize a new BRDF.
         */
        BxDF(std::map<std::string, std::string> parameters = std::map<std::string, std::string>());

        /**
         * Destructor.
         */
        ~BxDF();

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
