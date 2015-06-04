#include <map>
#include <string>
#include <glm/glm.hpp>

#include "Placeholder/Renderer.hpp"
#include "Placeholder/Camera.hpp"

#ifndef _Placeholder
#define _Placeholder

typedef std::map<std::string, std::string> StringMap;

/**
    Defines the interface for all renderers.
*/
class Placeholder {
    protected:
        Renderer * renderer;
    public:
        Placeholder();

        Renderer * getRenderer();
        void render(float[]);
};

#endif
