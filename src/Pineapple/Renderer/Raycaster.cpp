#include "Pineapple/Renderer/Raycaster.hpp"

#include "Pineapple/Scene.hpp"
#include "Pineapple/Integrator/SurfaceIntegrator.hpp"
#include "Pineapple/Integrator/SurfaceColorIntegrator.hpp"
#include "Pineapple/Integrator/SurfaceDepthIntegrator.hpp"

Raycaster::Raycaster(std::map<std::string, std::string> parameters) :
        Renderer(parameters) {
    std::map<std::string, std::string>::const_iterator end = parameters.end();

    std::string inIntegrator = "default";
    if (parameters.find("integrator") != end) {
        inIntegrator = parameters["integrator"];
    }

    if (inIntegrator == "default") {
        // TODO Set default as SurfaceMaterialIntegrator
        integrators.push_back(new SurfaceDepthIntegrator());
    }
    else if (inIntegrator == "depth") {
        integrators.push_back(new SurfaceDepthIntegrator());
    }
    else if (inIntegrator == "color") {
        integrators.push_back(new SurfaceColorIntegrator());
    }
}

Raycaster::~Raycaster() {

}

void Raycaster::render(float imageBuffer[], Scene * scene) {
    Camera * c = scene->getCamera();
    int width = c->viewport.x;
    int height = c->viewport.y;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Ray ray = c->getRay(((float) j + 0.5f) / width, ((float) i + 0.5f) / height);
            int offset = (i * width + j) * 4;

            glm::vec4 color;
            for (std::vector<SurfaceIntegrator *>::iterator k = integrators.begin(); k != integrators.end(); k++) {
                color += (*k)->shade(ray, scene);
            }

            imageBuffer[offset + 0] = color.r;
            imageBuffer[offset + 1] = color.g;
            imageBuffer[offset + 2] = color.b;
            imageBuffer[offset + 3] = color.a;
        }
    }
}
