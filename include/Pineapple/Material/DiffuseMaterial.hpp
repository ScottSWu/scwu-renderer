#ifndef _Pineapple_Material_Diffuse
#define _Pineapple_Material_Diffuse

class Intersection;
class Ray;
class Scene;

#include "Pineapple/Material.hpp"

#include <glm/glm.hpp>

#include <stack>

class DiffuseMaterial: public Material {
    public:
        /**
         * Initialize a new diffuse material.
         */
        DiffuseMaterial(std::map<std::string, std::string> parameters = std::map<std::string, std::string>());

        /**
         * Destructor.
         */
        ~DiffuseMaterial();

        /**
         * Sample a color from this material from an intersection result.
         *
         * @param rays      The stack of rays being processed
         * @param ray       The current intersected ray
         * @param result    The intersection result
         * @param scene     The intersected scene
         * @return      The sampled color
         */
        glm::vec4 sampleColor(std::stack<Ray> & rays, const Ray ray, const Intersection & result, Scene * scene);
};

#endif
