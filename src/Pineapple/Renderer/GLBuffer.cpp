#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Pineapple/Renderer/GLBuffer.hpp"
#include "Pineapple/Shape/Mesh.hpp"
#include "Pineapple/Shape/Vertex.hpp"
#include "Pineapple/Shape/Triangle.hpp"

#include <stdio.h>

GLBuffer::GLBuffer(Mesh & m) {
    // Set the parent
    parent = m;
    
    // Fill buffers
    int vertices = m.vertices.size();
    int faces = m.faces.size();

    // Positions
    glGenBuffers(1, &positionBuffer);
    std::vector<glm::vec3> positionList;
    for (int i = 0; i < vertices; i++)
        positionList.push_back(m.vertices[i].position);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(glm::vec3), &(positionList)[0], GL_STATIC_DRAW);

    // Normals
    glGenBuffers(1, &normalBuffer);
    std::vector<glm::vec3> normalList;
    for (int i = 0; i < vertices; i++)
        normalList.push_back(m.vertices[i].normal);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(glm::vec3), &(normalList)[0], GL_STATIC_DRAW);
    
    // UVs
    if (m.hasUVs) {
        glGenBuffers(1, &uvBuffer);
        std::vector<glm::vec2> uvList;
        for (int i = 0; i < vertices; i++)
            uvList.push_back(m.vertices[i].uv);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(glm::vec2), &(uvList)[0], GL_STATIC_DRAW);
    }

    // Colors
    if (m.hasColors) {
        glGenBuffers(1, &colorBuffer);
        std::vector<glm::vec4> colorList;
        for (int i = 0; i < vertices; i++)
            colorList.push_back(m.vertices[i].color);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, vertices * sizeof(glm::vec4), &(colorList)[0], GL_STATIC_DRAW);
    }
    
    // Assign indices
    glGenBuffers(1, &indexBuffer);
    if (m.wireframe) { // Reindex vertices to work with GL_LINES
        std::vector<unsigned int> indices;
        
        glm::uvec3 index;
        for (int i = 0; i < faces; i++) {
            Triangle face = m.faces[i];
            index = face.getIndices();
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
            Triangle face = m.faces[i];
            index = face.getIndices();
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
    
    if (parent.hasUVs) {
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }
    if (parent.hasColors) {
        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(mode, indexSize, GL_UNSIGNED_INT, 0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    if (parent.hasUVs) {
        glDisableVertexAttribArray(2);
    }
    if (parent.hasColors) {
        glDisableVertexAttribArray(3);
    }
}
