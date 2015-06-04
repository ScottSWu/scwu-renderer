#include "Placeholder/Camera.hpp"

#ifndef _Placeholder_Renderer
#define _Placeholder_Renderer

/**
    Defines an arbitrary renderer.
*/
class Renderer {
    protected:
        Camera camera;
    public:
        Renderer();

        virtual void render(float[]);

        void setCameraViewport(int, int);
        void setCameraPosition(float, float, float);
        void setCameraTarget(float, float, float);
};

#endif
