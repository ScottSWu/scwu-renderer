#include "Pineapple/Shape/Mesh.hpp"

Mesh::Mesh(Material * inMaterial) :
        Surface(inMaterial), hasUVs(false), hasColors(false) {
    
}

void Mesh::computeNormals() {
    // TODO Compute normals
}

void Mesh::mergeVertices(float threshold) {
    // TODO merge vertices
}
