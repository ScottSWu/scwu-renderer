#include "Pineapple/Camera.hpp"

#ifndef _Pineapple_Renderer
#define _Pineapple_Renderer

class Renderer {
    protected:
        Camera camera;
    public:
        Renderer();

        virtual void render(float[]);
        
        void setViewport(int, int);
};

#endif
