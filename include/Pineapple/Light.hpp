#ifndef _Pineapple_Light
#define _Pineapple_Light

#include "Pineapple/Object3d.hpp"

class Scene;

#include <glm/glm.hpp>

/**
 * Defines a light source.
 */
class Light: public Object3d {
    public:
        /**
         * Initialize a new light at a given position and color.
         *
         * @param position  The position of the light
         * @param color     The color of the light
         * @param type      The type of light
         */
        Light(glm::vec4 inPosition = glm::vec4(0.f, 0.f, 0.f, 1.f), glm::vec4 inColor = glm::vec4(1.f, 1.f, 1.f, 1.f),
                int inType = 0);

        /**
         * Destructor
         */
        virtual ~Light();

        /**
         * The type of light.
         */
        int type;
        /**
         * The position of the light.
         */
        glm::vec4 position;
        /**
         * The color of the light.
         */
        glm::vec4 color;

        /**
         * Light types
         */
        static const int TYPE_AMBIENT = 0;
        static const int TYPE_POINT = 1;
        static const int TYPE_DIRECTIONAL = 2;

        /**
         * Get the light factor to a point.
         *
         * @param scene     The scene object
         * @param position  The position of the point
         * @param normal    The normal at the point
         */
        virtual glm::vec4 getFactor(Scene * scene, glm::vec4 position, glm::vec4 normal);
};

#endif
