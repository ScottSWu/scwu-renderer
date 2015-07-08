#include "Pineapple/Shape/Mesh.hpp"

#include "Pineapple/Intersection.hpp"
#include "Pineapple/Ray.hpp"
#include "Pineapple/Util/Intersect.hpp"

Mesh::Mesh(Material * inMaterial) :
        Surface(inMaterial), vertexCount(0), faceCount(0) {
    
}

Mesh::~Mesh() {

}

void Mesh::fillDefault() {
    if (normals.size() < vertexCount) {
        computeNormals();
    }

    while (uvs.size() < vertexCount) {
        uvs.push_back(glm::vec2(0.f, 0.f));
    }

    while (colors.size() < vertexCount) {
        colors.push_back(glm::vec4(1.f, 1.f, 1.f, 1.f));
    }

    computeBoundingBox();

    material->loadTextures();
}

void Mesh::computeNormals() {
    glm::vec3 a, b, c;
    glm::vec4 fn;

    // Clear vertex normals
    normals.clear();
    for (int i = 0; i < vertexCount; i++) {
        normals.push_back(glm::vec4());
    }

    // Compute face normals and add to vertices
    faceNormals.clear();
    for (int i = 0; i < faceCount; i++) {
        a = glm::vec3(positions[faces[i].x]);
        b = glm::vec3(positions[faces[i].y]) - a;
        c = glm::vec3(positions[faces[i].z]) - a;
        fn = glm::vec4(glm::normalize(glm::cross(b, c)), 0.f);
        faceNormals.push_back(fn);

        normals[faces[i].x] = normals[faces[i].x] + fn;
        normals[faces[i].y] = normals[faces[i].y] + fn;
        normals[faces[i].z] = normals[faces[i].z] + fn;
    }

    // Normalize all normals
    for (int i = 0; i < vertexCount; i++) {
        normals[i] = glm::normalize(normals[i]);
    }
}

BoundingBox Mesh::computeBoundingBox() {
    glm::vec3 min, max;
    for (int i = 0; i < vertexCount; i++) {
        if (positions[i].x < min.x) {
            min.x = positions[i].x;
        }
        if (positions[i].x > max.x) {
            max.x = positions[i].x;
        }
        if (positions[i].y < min.y) {
            min.y = positions[i].y;
        }
        if (positions[i].y > max.y) {
            max.y = positions[i].y;
        }
        if (positions[i].z < min.z) {
            min.z = positions[i].z;
        }
        if (positions[i].z > max.z) {
            max.z = positions[i].z;
        }
    }

    bounds = BoundingBox(min, max);

    return bounds;
}

glm::vec4 Mesh::sampleColor(glm::uvec3 index, glm::vec3 coord) {
    // Since obj files do not support vertex colors, only check for textures
    if (material->textures.size() > 0) {
        glm::vec2 uv;
        uv += uvs[index.x] * coord.x;
        uv += uvs[index.y] * coord.y;
        uv += uvs[index.z] * coord.z;
        return material->sampleTexture(0, uv, glm::uvec2(0, 0));
    }
    else {
        return glm::vec4(1.f, 1.f, 1.f, 1.f);
    }
}

int Mesh::intersect(std::vector<Intersection> & results, const Ray & ray, bool recursive, int limit) {
    int count = 0;

    if (bounds.intersects(ray)) {
        for (int i = 0; i < faceCount; i++) {
            glm::vec4 result;
            glm::uvec3 index = faces[i];
            if (IntersectTriangle(result, ray, positions[index.x], positions[index.y], positions[index.z])) {
                Intersection next(result.w, this, index, glm::vec3(result.x, result.y, result.z));
                results.push_back(next);
                count++;
            }
        }
    }

    if (recursive) {
        for (int i = 0; i < children.size(); i++) {
            children[i]->intersect(results, ray, recursive, limit);
        }
    }

    return count;
}
