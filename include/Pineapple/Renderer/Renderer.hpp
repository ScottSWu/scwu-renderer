#include "Pineapple/Camera.hpp"

#ifndef _Pineapple_Renderer
#define _Pineapple_Renderer

/**
    Defines an arbitrary renderer.
*/
class Renderer {
    protected:
        /**
            Count of registered renderers
        */
        static int RENDERER_COUNT = 0;
        /**
            This renderer's id
        */
        int renderId = -1;
        /**
            Assign this renderer an id to store in objects.
        */
        void registerRenderer();
    public:
        /**
            Initialize a new renderer.
        */
        Renderer();

        /**
            Render the image to a float array.
            The size of the given array must be greater than 4 * width * height.

            @param imageBuffer  Float array to render to
            @param scene        Scene root
            @param camera       The scene camera
            @param lights       List of scene lights
        */
        virtual void render(float[], Object3d, Camera, std::vector<Light>);
};

#endif
