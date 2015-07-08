#include "Pineapple/Renderer/GLBuffer.hpp"

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
    std::vector<unsigned int> indices;

    glm::uvec3 index;
    for (int i = 0; i < faces; i++) {
        index = m->faces[i];
        indices.push_back(index.x);
        indices.push_back(index.y);
        indices.push_back(index.z);
    }

    indexSize = faces * 3;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(unsigned int), &(indices)[0], GL_STATIC_DRAW);

    if (m->wireframe) {
        mode = GL_LINE;
    }
    else {
        mode = GL_FILL;
    }
}

void GLBuffer::loadTexture(FIBITMAP * image) {
    textureSet.load(image, GL_RGB);
}

void GLBuffer::bind(const GLShader & shader) {
    // Bind to the shader
    textureSet.bind(shader);

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
}

void GLBuffer::render() {
    // Draw
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
}

void GLBuffer::unbind() {
    // Disable vertex arrays
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}
