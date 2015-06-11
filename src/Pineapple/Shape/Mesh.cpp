#include "Pineapple/Shape/Mesh.hpp"

Mesh::Mesh(Material * inMaterial) :
        Surface(inMaterial) {
    
}

void Mesh::fillDefault() {
    while (uvs.size() < vertexCount) {
        uvs.push_back(glm::vec2(0.f, 0.f));
    }

    while (colors.size() < vertexCount) {
        colors.push_back(glm::vec4(1.f, 1.f, 1.f, 1.f));
    }

    computeNormals();
}

void Mesh::computeNormals() {
    // TODO Compute normals
}

void Mesh::mergeVertices(float threshold) {
    // TODO merge vertices
}
