#ifndef _Pineapple
#define _Pineapple

#include "Pineapple/RenderBuffer.hpp"

class RenderBuffer;
class Renderer;
class Scene;
class TaskRunner;

#define GLFW_INCLUDE_GLU
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <stdio.h>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * Defines the interface for all renderers.*
 */
class Pineapple {
    protected:
        /** Offline renderer */
        Renderer * renderer;
        /** OpenGL visualizer */
        Renderer * visualizer;

        /** Scene */
        Scene * scene;

        /**
         * The current buffer being rendered to.
         */
        RenderBuffer * currentBuffer;

        /**
         * The current task runner.
         */
        TaskRunner * runner;
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
         * Set the current renderer given a number of parameters.
         *
         * @param params    String map of parameters
         * @return  Whether or not the setting was successful
         */
        bool setRenderer(std::map<std::string, std::string>);

        /**
         * Return the current scene.
         *
         * @return  A pointer to the current scene
         */
        Scene * getScene();

        /**
         * Render an image to an array. The result can be obtained by calling getRenderBuffer.
         *
         * @return  Whether or not the initialization was successful
         */
        bool render();
        /**
         * Visualize the scene in the current OpenGL context
         */
        void visualize();

        /**
         * Return the current image buffer being rendered to.
         *
         * @return A pointer to the rendering target buffer
         */
        RenderBuffer * getRenderBuffer();
};

#endif
