#include "Pineapple/Material/GlassMaterial.hpp"

#include "Pineapple/Intersection.hpp"
#include "Pineapple/Light.hpp"
#include "Pineapple/Ray.hpp"
#include "Pineapple/Scene.hpp"

GlassMaterial::GlassMaterial(std::map<std::string, std::string> parameters) :
        Material(parameters), indexOfRefraction(1.5), tMix(0.8), rMix(0.1), cMix(0.1), maxDepth(10) {
    auto itrEnd = parameters.end();
    if (parameters.find("indexOfRefraction") != itrEnd) {
        indexOfRefraction = std::stof(parameters["indexOfRefraction"]);
    }
    if (parameters.find("tMix") != itrEnd) {
        tMix = std::stof(parameters["tMix"]);
    }
    if (parameters.find("rMix") != itrEnd) {
        rMix = std::stof(parameters["rMix"]);
    }
    if (parameters.find("cMix") != itrEnd) {
        cMix = std::stof(parameters["cMix"]);
    }
    if (parameters.find("maxDepth") != itrEnd) {
        maxDepth = std::stoi(parameters["maxDepth"]);
    }
}

GlassMaterial::~GlassMaterial() {

}

glm::vec4 GlassMaterial::sampleColor(FastStack<Ray> & rays, const Ray ray, const Intersection & result, Scene * scene) {
    glm::vec4 position = result.surface->worldTransform * result.surface->samplePosition(result.index, result.coord);
    glm::vec4 normal = glm::normalize(
            result.surface->worldTransformIT * result.surface->sampleNormal(result.index, result.coord));
    glm::vec4 color = result.surface->sampleColor(result.index, result.coord);

    glm::vec4 totalColor;
    if (cMix > 0) {
        std::vector<Light *> lights = scene->getLights();
        for (int i = 0, l = lights.size(); i < l; i++) {
            Light * light = lights[i];
            glm::vec4 factor = light->getFactor(scene, position, normal);
            totalColor += light->color * factor;
        }
    }
    if (ray.depth < maxDepth) {
        // TODO Fresnel equation dictates mix
        if (tMix > 0) {
            glm::vec4 strength = ray.strength * tMix;
            Ray refracted(ray.depth + 1, position, refract(ray.direction, normal, indexOfRefraction), strength,
            PAC_EPSILON);
            rays.push(refracted);
        }
        if (rMix > 0) {
            glm::vec4 strength = ray.strength * rMix;
            Ray reflected(ray.depth + 1, position, reflect(ray.direction, normal), strength, PAC_EPSILON);
            rays.push(reflected);
        }
    }
    return totalColor * (cMix > 0 ? cMix : 0.f) * ray.strength;
}
