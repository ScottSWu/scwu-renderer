#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Pineapple/GLBuffer.hpp"

/**
    Create vertex arrays and buffer given a mesh. Must be done within a gl context.
*/
GLBuffer::GLBuffer(const Mesh & m) {
    parent = m;

    // Vertex arrays
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, m.vertices.size() * sizeof(glm::vec3), &(m.vertices)[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, m.normals.size() * sizeof(glm::vec3), &(m.normals)[0], GL_STATIC_DRAW);

    // Indexing
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.faces.size() * sizeof(glm::ivec3), &(m.faces)[0], GL_STATIC_DRAW);

    indexSize = m.faces.size() * 3;
}

void GLBuffer::render() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
