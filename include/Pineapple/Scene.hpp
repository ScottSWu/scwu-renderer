#ifndef _Pineapple_Scene
#define _Pineapple_Scene

#include <glm/glm.hpp>
#include <vector>

#include "Pineapple/Camera/OrthographicCamera.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/Light.hpp"

class Scene {
    protected:
        /** List of objects in the scene */
        std::vector<Object3d *> objects;
        /** List of lights in the scene */
        std::vector<Light *> lights;
    public:
        /**
         * Initialize a new scene with a camera.
         */
        Scene(Camera * inCamera = new OrthographicCamera(320, 320, -1.f, 1.f, 1.f, -1.f, 0.1, 100.f));

        /** Viewing camera */
        Camera * camera;

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
        void addObject(Object3d *);
        /**
         * Remove an object from the scene.
         *
         * @param object   The object to remove
         */
        void removeObject(Object3d *);

        /**
         * Add a light to the scene.
         *
         * @param light    The light to add
         */
        void addLight(Light *);
        /**
         * Remove a light from the scene.
         *
         * @param light    The light to remove
         */
        void removeLight(Light *);
};

#endif
