#include "Pineapple/Integrator/SurfaceDepthIntegrator.hpp"

#include "Pineapple/Intersection.hpp"
#include "Pineapple/Scene.hpp"
#include "Pineapple/Ray.hpp"

SurfaceDepthIntegrator::SurfaceDepthIntegrator() :
        SurfaceIntegrator() {

}

SurfaceDepthIntegrator::~SurfaceDepthIntegrator() {

}

glm::vec4 SurfaceDepthIntegrator::shade(const Ray & ray, Scene * scene) {
    Object3d * root = scene->getRoot();
    std::vector<Intersection> results;

    root->intersect(results, ray, true);

    float firstValue = 0.f;
    int firstIndex = -1;
    for (int i = 0, l = results.size(); i < l; i++) {
        float depth = results[i].t;
        if (firstIndex < 0 || depth < firstValue) {
            firstValue = depth;
            firstIndex = i;
        }
    }

    if (firstValue < 0.f) {
        return glm::vec4();
    }
    else {
        Camera * camera = scene->getCamera();
        float nlog = log10(camera->planes.x);
        float flog = log10(camera->planes.y);
        float dlog = log10(firstValue);
        float gray = 1.f - (dlog - nlog) / (flog - nlog);
        return glm::vec4(gray, gray, gray, 1.f);
    }
}
