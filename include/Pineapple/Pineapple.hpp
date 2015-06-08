#ifndef _Pineapple
#define _Pineapple

#include <glm/glm.hpp>
#include <map>
#include <string>
#include <vector>

#include "Pineapple/Scene.hpp"
#include "Pineapple/Renderer.hpp"
#include "Pineapple/Renderer/GLRenderer.hpp"
#include "Pineapple/Camera.hpp"

/**
 * Defines the interface for all renderers.
 */
class Pineapple {
    protected:
        /** Offline renderer */
        Renderer * renderer;
        /** OpenGL visualizer */
        Renderer * visualizer;

        /** Scene */
        Scene * scene;
    public:
        /**
         * Initialize a renderer and visualizer.
         */
        Pineapple();

        /**
         * Return the current renderer.
         *
         * @return  A pointer to the current renderer
         */
        Renderer * getRenderer();
        /**
         * Return the current scene.
         *
         * @return  A pointer to the current scene
         */
        Scene * getScene();

        /**
         * Render an image to an array.
         *
         * @param imageBuffer  Array to render to
         */
        void render(float[]);
        /**
         * Visualize the scene in the current OpenGL context
         */
        void visualize();
};

#endif
