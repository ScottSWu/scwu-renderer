#include "Pineapple/Material/BxDF.hpp"

#include "Pineapple/Intersection.hpp"
#include "Pineapple/Ray.hpp"

BxDF::BxDF(std::map<std::string, std::string> parameters) :
        Material(parameters) {
    auto itrEnd = parameters.end();

    if (parameters.find("subtype") != itrEnd) {
        std::string subtype = parameters["subtype"];
        if (subtype == "emissive") {
            type = TYPE_EMISSIVE;
        }
        else if (subtype == "diffuse") {
            type = TYPE_DIFFUSE;
        }
        else if (subtype == "glass") {
            type = TYPE_GLASS;
        }
    }

    if (parameters.find("color") != itrEnd) {
        color = getColor(parameters["color"]);
    }
    else {
        color = glm::vec4(1.f, 1.f, 1.f, 1.f);
    }

    if (parameters.find("altColor") != itrEnd) {
        altColor = getColor(parameters["altColor"]);
    }
    else {
        altColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
    }

    if (parameters.find("intensity") != itrEnd) {
        intensity = std::stof(parameters["intensity"]);
    }
    else {
        intensity = 0.f;
    }

    if (parameters.find("altIntensity") != itrEnd) {
        altIntensity = std::stof(parameters["altIntensity"]);
    }
    else {
        altIntensity = 0.f;
    }

    if (parameters.find("attribute") != itrEnd) {
        attribute = std::stof(parameters["attribute"]);
    }
    else {
        attribute = 0.f;
    }

    if (parameters.find("altAttribute") != itrEnd) {
        altAttribute = std::stof(parameters["altAttribute"]);
    }
    else {
        altAttribute = 0.f;
    }

    if (parameters.find("maxDepth") != itrEnd) {
        maxDepth = std::stoi(parameters["maxDepth"]);
    }
    else {
        maxDepth = 20;
    }
}

BxDF::~BxDF() {

}

glm::vec4 BxDF::sampleColor(FastStack<Ray> & rays, const Ray ray, const Intersection & result, Scene * scene) {
    glm::vec4 position = result.surface->worldTransform * result.surface->samplePosition(result.index, result.coord);
    glm::vec4 normal = glm::normalize(
            result.surface->worldTransformIT * result.surface->sampleNormal(result.index, result.coord));

    float p = SampleUniform();
    glm::vec4 totalColor(0.f, 0.f, 0.f, 1.f);

    if (ray.depth < maxDepth) {
        if (type == TYPE_EMISSIVE) {
            totalColor = intensity * color;
        }
        else if (type == TYPE_DIFFUSE) {
            glm::vec4 strength = ray.strength * color;
            glm::vec4 outgoing = SampleHemi(normal);
            Ray reflected(ray.depth + 1, position, outgoing, strength, PAC_EPSILON);
            rays.push(reflected);
        }
        else if (type == TYPE_GLASS) {
            // TODO Fresnel equation dictates mix
            if (intensity > 0) { // Refractive
                glm::vec4 strength = ray.strength * intensity;
                Ray refracted(ray.depth + 1, position, refract(ray.direction, normal, attribute), strength,
                PAC_EPSILON);
                rays.push(refracted);
            }
            if (altIntensity > 0) { // Reflective
                glm::vec4 strength = ray.strength * altIntensity;
                Ray reflected(ray.depth + 1, position, reflect(ray.direction, normal), strength, PAC_EPSILON);
                rays.push(reflected);
            }
        }
    }

    return totalColor * ray.strength;
}
