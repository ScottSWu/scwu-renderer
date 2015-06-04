#include <GLFW/glfw3.h>
#include <stdio.h>

#include "Pineapple/Pineapple.hpp"
#include "Pineapple/GLRenderer.hpp"

Pineapple::Pineapple() {
    renderer = new GLRenderer();
}

Renderer * Pineapple::getRenderer() {
    return renderer;
}

/**
    Render an image to an array.
*/
void Pineapple::render(float imageBuffer[]) {
    renderer->render(imageBuffer);
}
