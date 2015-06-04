#include <GLFW/glfw3.h>
#include <stdio.h>

#include "Placeholder/Placeholder.hpp"
#include "Placeholder/GLRenderer.hpp"

Placeholder::Placeholder() {
    renderer = new GLRenderer();
}

/**
    Return the current renderer.
*/
Renderer * Placeholder::getRenderer() {
    return renderer;
}

/**
    Render an image to an array.

    @param imageBuffer  Array to render to
*/
void Placeholder::render(float imageBuffer[]) {
    renderer->render(imageBuffer);
}
