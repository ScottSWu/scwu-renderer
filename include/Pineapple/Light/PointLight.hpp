#ifndef _Pineapple_Light_Point
#define _Pineapple_Light_Point

#include "Pineapple/Light.hpp"

class Scene;

#include "Pineapple/Globals.hpp"

/**
 * Defines a point light, with inverse distance squared falloff.
 */
class PointLight: public Light {
    public:
        /**
         * Initialize a new point light with an intensity.
         *
         * @param position      The position of the light
         * @param color         The color of the light
         * @param intensity     The intensity of the light
         */
        PointLight(glm::vec4 inPosition = glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4 inColor = glm::vec4(1.f, 1.f, 1.f, 1.f), float inIntensity = 1.f);

        /**
         * Destructor
         */
        ~PointLight();

        /**
         * The intensity of the light.
         */
        float intensity;

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
