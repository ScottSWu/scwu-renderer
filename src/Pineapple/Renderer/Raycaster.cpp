#include "Pineapple/Renderer/Raycaster.hpp"

#include "Pineapple/Integrator/SurfaceIntegrator.hpp"
#include "Pineapple/Integrator/SurfaceColorIntegrator.hpp"
#include "Pineapple/Integrator/SurfaceDepthIntegrator.hpp"
#include "Pineapple/Integrator/SurfaceMaterialIntegrator.hpp"
#include "Pineapple/RenderBuffer.hpp"
#include "Pineapple/RenderTask.hpp"
#include "Pineapple/Scene.hpp"

Raycaster::Raycaster(std::map<std::string, std::string> parameters) :
        Renderer(parameters), samples(1) {
    std::map<std::string, std::string>::const_iterator end = parameters.end();

    std::string inIntegrator = "default";
    if (parameters.find("integrator") != end) {
        inIntegrator = parameters["integrator"];
    }

    if (parameters.find("samples") != end) {
        samples = std::stoi(parameters["samples"]);
    }

    // TODO Constant selector function
    if (inIntegrator == "default") {
        integrators.push_back(new SurfaceMaterialIntegrator());
    }
    else if (inIntegrator == "depth") {
        integrators.push_back(new SurfaceDepthIntegrator());
    }
    else if (inIntegrator == "color") {
        integrators.push_back(new SurfaceColorIntegrator());
    }
    else if (inIntegrator == "material") {
        integrators.push_back(new SurfaceMaterialIntegrator());
    }
}

Raycaster::~Raycaster() {

}

void Raycaster::init(RenderBuffer * inBuffer, Scene * inScene) {
    Renderer::init(inBuffer, inScene);

    currentScene->computeBoundingBox(true);
    currentScene->computeTransform();

    // Go by rows for now

    for (int i = 0; i < height; i++) {
        tasks.push(new RenderTask(width, 1, 0, i, samples));
    }
}

void Raycaster::render(RenderTask * task) {
    Camera * c = currentScene->getCamera();
    int width = c->viewport.x;
    int height = c->viewport.y;

    // TODO Respect samples variable

    float * buffer = task->data;
    int twidth = task->width;
    int theight = task->height;
    int tx = task->x;
    int ty = task->y;
    int ts = task->samples;

    // Sample spacing
    float ss = 1.f / (float) ts;
    // Half sample spacing (to center)
    float hss = ss / 2.f;
    // Total samples
    float totalSamples = ts * ts;

    // Each task
    for (int i = 0; i < theight; i++) {
        for (int j = 0; j < twidth; j++) {
            int offset = (i * twidth + j) * 4;
            glm::vec4 color;

            // Each sample
            for (int si = 0; si < ts; si++) {
                for (int sj = 0; sj < ts; sj++) {
                    float offsetX = (j + tx + ss * sj + hss) / width;
                    float offsetY = (i + ty + ss * si + hss) / height;
                    Ray ray = c->getRay(offsetX, offsetY);

                    for (auto k = integrators.begin(); k != integrators.end(); k++) {
                        color += (*k)->shade(ray, currentScene);
                    }
                }
            }

            color = color / totalSamples;
            buffer[offset + 0] = color.r;
            buffer[offset + 1] = color.g;
            buffer[offset + 2] = color.b;
            buffer[offset + 3] = color.a;
        }
    }
}

void Raycaster::process(RenderTask * task) {
    float * buffer = task->data;
    int twidth = task->width;
    int theight = task->height;
    int tx = task->x;
    int ty = task->y;

    float * gbuffer = currentBuffer->buffer;
    for (int i = 0; i < theight; i++) {
        for (int j = 0; j < twidth; j++) {
            int offset = (i * twidth + j) * 4;
            int goffset = ((i + ty) * width + (j + tx)) * 4;

            gbuffer[goffset + 0] = buffer[offset + 0];
            gbuffer[goffset + 1] = buffer[offset + 1];
            gbuffer[goffset + 2] = buffer[offset + 2];
            gbuffer[goffset + 3] = buffer[offset + 3];
        }
    }
}

bool Raycaster::hasTask() {
    return !tasks.empty();
}

RenderTask * Raycaster::getTask() {
    RenderTask * task = tasks.front();
    tasks.pop();
    return task;
}
