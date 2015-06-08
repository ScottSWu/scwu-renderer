#include <glm/glm.hpp>
#include <map>
#include <string>
#include <vector>

#include "Pineapple/Renderer.hpp"
#include "Pineapple/Camera.hpp"

#ifndef _Pineapple
#define _Pineapple

typedef std::map<std::string, std::string> StringMap;

/**
 Defines the interface for all renderers.
 */
class Pineapple {
    protected:
        /** Offline renderer */
        Renderer * renderer;
        /** OpenGL visualizer */
        Renderer * visualizer;

        /** Camera */
        Camera camera;
        /** Scene root */
        Object3d scene;
        /** List of lights */
        std::vector<Light> lights;
    public:
        /**
         * Initialize a renderer and visualizer.
         */
        Pineapple();

        /**
         * Return the current renderer.
         */
        Renderer * getRenderer();

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

        /**
         * Set the camera viewport size.
         *
         * @param width    Viewport width
         * @param height   Viewport height
         */
        void setCameraViewport(int, int);
        /**
         * Set the camera position.
         *
         * @param x    x coordinate
         * @param y    y coordinate
         * @param z    z coordinate
         */
        void setCameraPosition(float, float, float);
        /**
         * Set the camera viewing target.
         *
         * @param x    x coordinate
         * @param y    y coordinate
         * @param z    z coordinate
         */
        void setCameraTarget(float, float, float);

        /**
         * Add an object to the scene.
         *
         * @param object   The object to add
         */
        void addObject(Object3d);
        /**
         * Remove an object from the scene.
         *
         * @param object   The object to remove
         */
        void removeObject(Object3d);

        /**
         * Add a light to the scene.
         *
         * @param light    The light to add
         */
        void addLight(Light);
        /**
         * Remove a light from the scene.
         *
         * @param light    The light to remove
         */
        void removeLight(Light);
};

#endif
