#include <glm/glm.hpp>

#ifndef _Pineapple_Camera
#define _Pineapple_Camera

class Camera {
    public:
        Camera();
        
        glm::ivec2 viewport;
        glm::vec3 position;
        glm::vec3 orientation;
};

#endif
