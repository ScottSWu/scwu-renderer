#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Pineapple/Renderer/GLBuffer.hpp"
#include "Pineapple/Shape/Mesh.hpp"

#include <stdio.h>

GLBuffer::GLBuffer() :
        shaderIndex(0), positionBuffer(-1), normalBuffer(-1), uvBuffer(-1), colorBuffer(-1), indexBuffer(-1), indexSize(
                0), mode(GL_LINES) {

}

GLBuffer::GLBuffer(Mesh * m) :
        shaderIndex(0) {
    // Fill buffers
    int vertices = m->vertexCount;
    int faces = m->faceCount;

    // Positions
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(glm::vec4), &(m->positions)[0], GL_STATIC_DRAW);

    // Normals
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(glm::vec4), &(m->normals)[0], GL_STATIC_DRAW);
    
    // UVs
    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(glm::vec2), &(m->uvs)[0], GL_STATIC_DRAW);

    // Colors
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(glm::vec4), &(m->colors)[0], GL_STATIC_DRAW);
    
    // Assign indices
    glGenBuffers(1, &indexBuffer);
    if (m->wireframe) { // Reindex vertices to work with GL_LINES
        std::vector<unsigned int> indices;
        
        glm::uvec3 index;
        for (int i = 0; i < faces; i++) {
            index = m->faces[i];
            indices.push_back(index.x);
            indices.push_back(index.y);
            indices.push_back(index.y);
            indices.push_back(index.z);
            indices.push_back(index.z);
            indices.push_back(index.x);
        }
        
        indexSize = faces * 6;
        mode = GL_LINES;
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(unsigned int), &(indices)[0], GL_STATIC_DRAW);
    }
    else { // Usual given indices
        std::vector<unsigned int> indices;
        
        glm::uvec3 index;
        for (int i = 0; i < faces; i++) {
            index = m->faces[i];
            indices.push_back(index.x);
            indices.push_back(index.y);
            indices.push_back(index.z);
        }
        
        indexSize = faces * 3;
        mode = GL_TRIANGLES;
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(unsigned int), &(indices)[0], GL_STATIC_DRAW);
    }
}

void GLBuffer::loadTexture(const char * filename) {
    textureSet.load(filename, GL_RGB);
}

void GLBuffer::bind(const GLShader & shader) {
    textureSet.bind(shader);
}

void GLBuffer::render() {
    // Enable vertex arrays
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // Draw
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(mode, indexSize, GL_UNSIGNED_INT, 0);
    
    // Disable vertex arrays
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}
