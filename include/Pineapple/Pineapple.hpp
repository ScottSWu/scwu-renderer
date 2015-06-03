#include <map>
#include <string>
#include <glm/glm.hpp>

#include "Pineapple/Renderer.hpp"
#include "Pineapple/Camera.hpp"

#ifndef _Pineapple
#define _Pineapple

typedef std::map<std::string, std::string> StringMap;

class Pineapple {
    protected:
        Renderer * renderer;
    public:
        Pineapple();

        Renderer * getRenderer();
        void render(float[]);
};

#endif
