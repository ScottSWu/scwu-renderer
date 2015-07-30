#ifndef _Pineapple_Light_Ambient
#define _Pineapple_Light_Ambient

#include "Pineapple/Light.hpp"

/**
 * Defines a point light, with inverse distance squared falloff.
 */
class AmbientLight: public Light {
    public:
        /**
         * Initialize a new point light with an intensity.
         *
         * @param position      The position of the light
         * @param color         The color of the light
         * @param intensity     The intensity of the light
         */
        AmbientLight(glm::vec4 inColor = glm::vec4(1.f, 1.f, 1.f, 1.f));

        /**
         * Destructor
         */
        ~AmbientLight();

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
