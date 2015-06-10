#include "Pineapple/Shape/Triangle.hpp"

Triangle::Triangle(Mesh * inParent, unsigned int inV0, unsigned int inV1, unsigned int inV2) {
    parent = inParent;
    vertex0 = inV0;
    vertex1 = inV1;
    vertex2 = inV2;
}

void Triangle::computeNormal() {
    glm::vec3 v0 = parent->vertices[vertex0].position;
    glm::vec3 v1 = parent->vertices[vertex1].position;
    glm::vec3 v2 = parent->vertices[vertex2].position;
    
    normal = glm::normalize(glm::cross(v0 - v1, v2 - v1));
}

glm::uvec3 Triangle::getIndices() {
    return glm::uvec3(vertex0, vertex1, vertex2);
}
