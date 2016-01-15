#include "Pineapple/Integrator/SurfaceColorIntegrator.hpp"

#include "Pineapple/Intersection.hpp"
#include "Pineapple/Scene.hpp"
#include "Pineapple/Ray.hpp"

SurfaceColorIntegrator::SurfaceColorIntegrator() :
        SurfaceIntegrator() {

}

SurfaceColorIntegrator::~SurfaceColorIntegrator() {

}

glm::vec4 SurfaceColorIntegrator::shade(const Ray & ray, Scene * scene) {
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

    if (firstIndex < 0) {
        return glm::vec4();
    }
    else {
        Intersection result = results[firstIndex];
        return result.surface->sampleColor(result.index, result.coord);
    }
}
