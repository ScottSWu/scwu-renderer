#include "Placeholder/Renderer.hpp"

/**
    Initialize a new renderer.
*/
Renderer::Renderer() {

}

/**
    Render the image to a float array.
    The size of the given array must be greater than 4 * width * height.

    @param imageBuffer  Float array to render to
*/
void Renderer::render(float imageBuffer[]) {

}

/**
    Set the camera viewport size.

    @param width    Viewport width
    @param height   Viewport height
*/
void Renderer::setCameraViewport(int width, int height) {
    camera.viewport = glm::ivec2(width, height);
}

/**
    Set the camera position.

    @param x    x coordinate
    @param y    y coordinate
    @param z    z coordinate
*/
void Renderer::setCameraPosition(float x, float y, float z) {
    camera.position = glm::vec3(x, y, z);
}

/**
    Set the camera viewing target.

    @param x    x coordinate
    @param y    y coordinate
    @param z    z coordinate
*/
void Renderer::setCameraTarget(float x, float y, float z) {
    camera.target = glm::vec3(x, y, z);
}
