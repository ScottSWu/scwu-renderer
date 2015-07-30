#ifndef _Pineapple_Light_Directional
#define _Pineapple_Light_Directional

#include "Pineapple/Light.hpp"

#include "Pineapple/Globals.hpp"

class Scene;

/**
 * Defines a point light, with inverse distance squared falloff.
 */
class DirectionalLight: public Light {
    public:
        /**
         * Initialize a new directional light. The position defines the
         * direction that the light is coming from.
         *
         * @param position      The position of the light
         * @param color         The color of the light
         */
        DirectionalLight(glm::vec4 inPosition = glm::vec4(0.f, 0.f, 0.f, 1.f),
                glm::vec4 inColor = glm::vec4(1.f, 1.f, 1.f, 1.f));

        /**
         * Destructor
         */
        ~DirectionalLight();

        /**
         * Get the light factor to a point.
         *
         * @param scene     The scene object
         * @param position  The position of the point
         * @param normal    The normal at the point
         */
        glm::vec4 getFactor(Scene * scene, glm::vec4 position, glm::vec4 normal);
};

#endif
