#include <stdlib.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include "Pineapple/Pineapple.hpp"
#include "Pineapple/Camera.hpp"

int main() {
    Pineapple p = *(new Pineapple());

    Camera c = p.getCamera();
    
    printf("Width: %d, Height: %d", c.viewport.x, c.viewport.y);

    return 0;
}
