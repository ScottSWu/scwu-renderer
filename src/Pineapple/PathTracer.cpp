#include "Pineapple/Renderer/PathTracer.hpp"

#include "Pineapple/Integrator/SurfaceIntegrator.hpp"
#include "Pineapple/Integrator/SurfaceColorIntegrator.hpp"
#include "Pineapple/Integrator/SurfaceDepthIntegrator.hpp"
#include "Pineapple/Integrator/SurfaceMaterialIntegrator.hpp"
#include "Pineapple/RenderBuffer.hpp"
#include "Pineapple/RenderTask.hpp"
#include "Pineapple/Scene.hpp"
#include "Pineapple/Util/Sampler.hpp"

PathTracer::PathTracer(std::map<std::string, std::string> parameters) :
        Renderer(parameters), samples(1), totalTasks(0), seed(0) {
    std::map<std::string, std::string>::const_iterator end = parameters.end();

    if (parameters.find("samples") != end) {
        samples = std::stoi(parameters["samples"]);
    }
    if (parameters.find("seed") != end) {
        seed = std::stoi(parameters["seed"]);
    }

    integrator = new SurfaceMaterialIntegrator();
}

PathTracer::~PathTracer() {

}

void PathTracer::init(RenderBuffer * inBuffer, Scene * inScene) {
    Renderer::init(inBuffer, inScene);

    currentScene->computeTransform();
    currentScene->computeBoundingBox(true);

    // First seed
    SampleSeed(seed);

    // Go by rows for now
    for (int i = 0; i < height; i++) {
        tasks.push(new RenderTask(width, 1, 0, i, samples, SampleInt()));
    }
    totalTasks = tasks.size();
}

void PathTracer::render(RenderTask * task) {
    Camera * c = currentScene->getCamera();
    int width = c->viewport.x;
    int height = c->viewport.y;

    float * buffer = task->data;
    int twidth = task->width;
    int theight = task->height;
    int tx = task->x;
    int ty = task->y;
    int ts = task->samples;

    // Task seed
    SampleSeed(task->seed);

    // Task size
    for (int i = 0; i < theight; i++) {
        for (int j = 0; j < twidth; j++) {
            int offset = (i * twidth + j) * 4;
            glm::vec4 color;

            // Each sample
            for (int s = 0; s < ts; s++) {
                float offsetX = (j + tx) / float(width);
                float offsetY = (i + ty) / float(height);
                Ray ray = c->getRay(offsetX, offsetY);
                color += integrator->shade(ray, currentScene);
            }

            color = color / float(ts);
            buffer[offset + 0] = color.r;
            buffer[offset + 1] = color.g;
            buffer[offset + 2] = color.b;
            buffer[offset + 3] = color.a;
        }
    }
}

void PathTracer::process(RenderTask * task) {
    // TODO VERIFY THAT THE TASK DATA FITS WITHIN THE BUFFER
    float * buffer = task->data;
    int twidth = task->width;
    int theight = task->height;
    int tx = task->x;
    int ty = task->y;

    if (tx + twidth >= width) {
        twidth = width - tx;
    }
    if (ty + theight >= height) {
        theight = height - ty;
    }

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

bool PathTracer::hasTask() {
    return !tasks.empty();
}

RenderTask * PathTracer::getTask() {
    RenderTask * task = tasks.front();
    tasks.pop();
    return task;
}

int PathTracer::getTaskCount() {
    return totalTasks;
}
