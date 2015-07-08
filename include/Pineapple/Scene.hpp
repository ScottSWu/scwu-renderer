#ifndef _Pineapple_Scene
#define _Pineapple_Scene

#include "Pineapple/Camera/OrthographicCamera.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/Light.hpp"

#include <glm/glm.hpp>

#include <vector>

class Scene {
    protected:
        /** Viewing camera */
        Camera * camera;
        /** Root scene object */
        Object3d * root;
        /** List of lights in the scene */
        std::vector<Light *> lights;
    public:
        /**
         * Initialize a new scene with a camera.
         */
        Scene(Camera * inCamera = new OrthographicCamera(320, 320, -1.f, 1.f, 1.f, -1.f, 0.1, 100.f));

        /**
         * Set the camera object.
         *
         * @param camera    Camera object to set to
         */
        void setCamera(Camera *);
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
         * Return the current camera.
         *
         * @return  The current camera
         */
        Camera * getCamera();

        /**
         * Return the root object.
         *
         * @return  The root object
         */
        Object3d * getRoot();

        /**
         * Return a list of objects.
         *
         * @return  A vector copy of object pointers
         */
        std::vector<Object3d *> getObjects();

        /**
         * Return a list of lights.
         *
         * @return  A vector copy of light pointers
         */
        std::vector<Light *> getLights();

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
