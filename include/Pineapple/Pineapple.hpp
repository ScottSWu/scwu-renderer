#include <map>
#include <string>
#include <glm/glm.hpp>
#include "Pineapple/Camera.hpp"

#ifndef _Pineapple
#define _Pineapple

typedef std::map<std::string, std::string> StringMap;

class Pineapple {
    protected:
        Camera camera;
    public:
        Pineapple();
        Camera getCamera() { return camera; };
};

#endif
