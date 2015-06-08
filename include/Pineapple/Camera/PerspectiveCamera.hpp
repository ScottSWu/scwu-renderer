#include <glm/glm.hpp>

#include "Pineapple/Camera.hpp"

#ifndef _Pineapple_Camera_Perspective
#define _Pineapple_Camera_Perspective

class PerspectiveCamera: public Camera {
    public:
        /** Field of view */
        float fov;
        /** Near and far planes */
        glm::vec2 planes;
};

#endif
