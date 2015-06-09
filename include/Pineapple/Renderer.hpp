#ifndef _Pineapple_Renderer
#define _Pineapple_Renderer

#include <vector>

#include "Pineapple/Camera.hpp"
#include "Pineapple/Light.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/Scene.hpp"

/**
 * Defines an arbitrary renderer.
 */
class Renderer {
    protected:
        /**
         * This renderer's id
         */
        int rendererId;
        /**
         * Assign this renderer an id to store in objects.
         */
        void registerRenderer();
    public:
        /**
         * Count of registered renderers
         */
        static int RENDERER_COUNT;

        /**
         * Initialize a new renderer.
         */
        Renderer();

        /**
         * Destructor
         */
        virtual ~Renderer();

        /**
         * Render the image to a float array.
         * The size of the given array must be greater than 4 * width * height.
         *
         * @param imageBuffer  Float array to render to
         * @param scene        Scene to render
         */
        virtual void render(float[], Scene *);
};

#endif
