#include "Pineapple/Integrator/SurfaceMaterialIntegrator.hpp"

#include "Pineapple/Light/DirectionalLight.hpp"
#include "Pineapple/Light/PointLight.hpp"
#include "Pineapple/Intersection.hpp"
#include "Pineapple/Material.hpp"
#include "Pineapple/Scene.hpp"
#include "Pineapple/Ray.hpp"

SurfaceMaterialIntegrator::SurfaceMaterialIntegrator() :
        SurfaceIntegrator() {

}

SurfaceMaterialIntegrator::~SurfaceMaterialIntegrator() {

}

glm::vec4 SurfaceMaterialIntegrator::shade(const Ray & ray, Scene * scene) {
    Object3d * root = scene->getRoot();
    std::stack<Ray> rays;
    glm::vec4 totalColor;

    // Add the first ray
    rays.push(ray);

    while (!rays.empty()) {
        // Get the next ray
        Ray ray = rays.top();
        rays.pop();

        // Intersect
        std::vector<Intersection> results;
        root->intersect(results, ray, true);

        // Find the closest intersection
        float firstValue = 0.f;
        int firstIndex = -1;
        for (int i = 0, l = results.size(); i < l; i++) {
            float depth = results[i].t;
            if (firstIndex < 0 || depth < firstValue) {
                firstValue = depth;
                firstIndex = i;
            }
        }

        if (firstIndex >= 0) {
            // Sample color from the material
            Intersection result = results[firstIndex];
            Material * mat = result.surface->material;

            totalColor += mat->sampleColor(rays, ray, result, scene);
        }
    }

    return totalColor;
}
