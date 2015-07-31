#include "Pineapple/Material/DiffuseMaterial.hpp"

#include "Pineapple/Intersection.hpp"
#include "Pineapple/Light.hpp"
#include "Pineapple/Scene.hpp"
#include "Pineapple/Ray.hpp"

DiffuseMaterial::DiffuseMaterial(std::map<std::string, std::string> parameters) :
        Material(parameters) {

}

DiffuseMaterial::~DiffuseMaterial() {

}

glm::vec4 DiffuseMaterial::sampleColor(FastStack<Ray> & rays, const Ray ray, const Intersection & result,
        Scene * scene) {
    glm::vec4 position = result.surface->worldTransform * result.surface->samplePosition(result.index, result.coord);
    glm::vec4 normal = glm::normalize(
            result.surface->worldTransformIT * result.surface->sampleNormal(result.index, result.coord));
    glm::vec4 color = result.surface->sampleColor(result.index, result.coord);

    std::vector<Light *> lights = scene->getLights();
    glm::vec4 totalColor;
    for (int i = 0, l = lights.size(); i < l; i++) {
        Light * light = lights[i];
        glm::vec4 factor = light->getFactor(scene, position, normal);
        totalColor += light->color * factor;
    }

    totalColor.w = 1.f;
    return totalColor * color * ray.strength;
}
