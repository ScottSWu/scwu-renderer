#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Placeholder/GLBuffer.hpp"

/**
    Create vertex arrays and buffer given a mesh. Must be done within a gl context.

    @param m    Reference to the parent mesh
*/
GLBuffer::GLBuffer(const Mesh & m) {
    parent = m;

    // Vertex arrays
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, m.vertices.size() * sizeof(glm::vec3), &(m.vertices)[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, m.vertexNormals.size() * sizeof(glm::vec3), &(m.vertexNormals)[0], GL_STATIC_DRAW);

    if (m.wireframe) { // Reindex vertices to work with GL_LINES
        std::vector<glm::uvec3> lines;

        for (int i=0, l=m.faces.size(); i<l; i+=3) {
            lines.push_back(m.faces[i]);
            lines.push_back(m.faces[i+1]);
            lines.push_back(m.faces[i+1]);
            lines.push_back(m.faces[i+2]);
            lines.push_back(m.faces[i+2]);
            lines.push_back(m.faces[i]);
        }

        // Indexing
        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, lines.size() * sizeof(glm::uvec3), &(lines)[0], GL_STATIC_DRAW);

        indexSize = m.faces.size() * 6;
        mode = GL_LINES;
    }
    else {
        // Indexing
        glGenBuffers(1, &indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m.faces.size() * sizeof(glm::ivec3), &(m.faces)[0], GL_STATIC_DRAW);

        indexSize = m.faces.size() * 3;
        mode = GL_TRIANGLES;
    }
}

/**
    Draw the current buffers.
*/
void GLBuffer::render() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(mode, indexSize, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
