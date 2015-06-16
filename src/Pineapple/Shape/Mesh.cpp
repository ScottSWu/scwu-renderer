#include "Pineapple/Shape/Mesh.hpp"

Mesh::Mesh(Material * inMaterial) :
        Surface(inMaterial), vertexCount(0), faceCount(0) {
    
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

void Mesh::mergeVertices(float threshold) {
    // TODO merge vertices
}
