#include "Pineapple/Material/BRDF.hpp"
#include "Pineapple/Intersection.hpp"
#include "Pineapple/Ray.hpp"

BRDF::BRDF(std::map<std::string, std::string> parameters) :
        Material(parameters) {
    auto itrEnd = parameters.end();

    if (parameters.find("diffuse") != itrEnd) {
        diffuseColor = getColor(parameters["diffuse"]);
    }
    else {
        diffuseColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
    }

    if (parameters.find("intensity") != itrEnd) {
        emissiveIntensity = std::atof(parameters["intensity"].c_str());
        emissiveProbability = 0.9f;
    }
    else {
        emissiveIntensity = -1.f;
        emissiveProbability = -1.f;
    }

    if (parameters.find("emissive") != itrEnd) {
        emissiveColor = getColor(parameters["emissive"]);
    }
    else {
        emissiveColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
    }

    if (parameters.find("maxDepth") != itrEnd) {
        maxDepth = std::stoi(parameters["maxDepth"]);
    }
    else {
        maxDepth = 20;
    }
}

BRDF::~BRDF() {

}

glm::vec4 BRDF::sampleColor(FastStack<Ray> & rays, const Ray ray, const Intersection & result, Scene * scene) {
    glm::vec4 position = result.surface->worldTransform * result.surface->samplePosition(result.index, result.coord);
    glm::vec4 normal = glm::normalize(
            result.surface->worldTransformIT * result.surface->sampleNormal(result.index, result.coord));

    float p = SampleUniform();
    glm::vec4 totalColor(0.f, 0.f, 0.f, 0.f);

    if (p < emissiveProbability) {
        totalColor = emissiveIntensity * emissiveColor / emissiveProbability;
    }
    else if (ray.depth < maxDepth) {
        glm::vec4 strength = ray.strength * diffuseColor;
        glm::vec4 outgoing = SampleHemi(normal);
        Ray reflected(ray.depth + 1, position, outgoing, strength, PAC_EPSILON);
        rays.push(reflected);
    }
    else {
        totalColor.a = 1.f;
    }

    return totalColor * ray.strength;
}
