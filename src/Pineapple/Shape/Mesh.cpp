#include "Pineapple/Shape/Mesh.hpp"

#include "Pineapple/Accel.hpp"
#include "Pineapple/Intersection.hpp"
#include "Pineapple/Ray.hpp"
#include "Pineapple/Util/FastStack.hpp"
#include "Pineapple/Util/Intersect.hpp"

Mesh::Mesh(Material * inMaterial) :
        Surface(inMaterial), vertexCount(0), faceCount(0), boundsNeedsUpdate(true) {
    
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

    // Compute face normals and add to vertex normals
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

BoundingBox Mesh::computeBoundingBox(bool recursive) {
    if (boundsNeedsUpdate) {
        // Compute min and max points
        glm::vec4 min, max;
        if (vertexCount > 0) {
            min = positions[0];
            max = positions[0];
            for (int i = 1; i < vertexCount; i++) {
                min = glm::min(min, positions[i]);
                max = glm::max(max, positions[i]);
            }
        }

        boundingBox = BoundingBox(glm::vec3(min), glm::vec3(max));
        totalBoundingBox = boundingBox;

        // Also generate an acceleration structure
        std::vector<int> indices;
        for (int i = 0; i < faceCount; i++) {
            indices.push_back(i);
        }
        accelStructure = generateAccelStructure(indices);

        boundsNeedsUpdate = false;
    }

    return boundingBox;
}

Accel * Mesh::generateAccelStructure(const std::vector<int> & indices) {
    // Simple binary trees split by widest center points for now

    int indexCount = indices.size();

    // Compute the bounding box and center point
    glm::vec4 min(boundingBox.maxBound, 1.f);
    glm::vec4 max(boundingBox.minBound, 1.f);
    glm::vec4 center;
    std::vector<glm::vec4> indexCenter;

    for (int i = 0; i < indexCount; i++) {
        glm::uvec3 index = faces[indices[i]];
        min = glm::min(min, positions[index.x]);
        min = glm::min(min, positions[index.y]);
        min = glm::min(min, positions[index.z]);

        max = glm::max(max, positions[index.x]);
        max = glm::max(max, positions[index.y]);
        max = glm::max(max, positions[index.z]);

        center = center + positions[index.x];
        center = center + positions[index.y];
        center = center + positions[index.z];

        indexCenter.push_back((positions[index.x] + positions[index.y] + positions[index.z]) / 3.f);
    }
    center = center / (indexCount * 3.f);

    // Just return if there are only a few triangles
    if (indexCount < 10) {
        Accel * node = new Accel();
        node->isLeaf = true;
        node->indices = indices;
        node->boundingBox = BoundingBox(glm::vec3(min), glm::vec3(max));
        return node;
    }

    // Otherwise compute the longest axis and sort
    int axis = 0;
    if (max.y - min.y > max[axis] - min[axis]) {
        axis = 1;
    }
    if (max.z - min.z > max[axis] - min[axis]) {
        axis = 2;
    }

    // Partition
    std::vector<int> left, right;
    for (int i = 0; i < indexCount; i++) {
        if (indexCenter[i][axis] < center[axis]) {
            left.push_back(indices[i]);
        }
        else {
            right.push_back(indices[i]);
        }
    }

    // Check if partitioning did nothing
    if (left.size() == indexCount || right.size() == indexCount) {
        // Then return a leaf node
        Accel * node = new Accel();
        node->isLeaf = true;
        node->indices = indices;
        node->boundingBox = BoundingBox(glm::vec3(min), glm::vec3(max));
        return node;
    }
    else {
        // Recurse
        Accel * node = new Accel();
        node->isLeaf = false;
        node->boundingBox = BoundingBox(glm::vec3(min), glm::vec3(max));
        node->children.push_back(generateAccelStructure(left));
        node->children.push_back(generateAccelStructure(right));
        return node;
    }
}

glm::vec4 Mesh::samplePosition(const glm::uvec3 & index, const glm::vec3 & coord) {
    glm::vec4 position;
    position += positions[index.x] * coord.x;
    position += positions[index.y] * coord.y;
    position += positions[index.z] * coord.z;
    position.w = 1.f;
    return position;
}

glm::vec4 Mesh::sampleNormal(const glm::uvec3 & index, const glm::vec3 & coord) {
    glm::vec4 normal;
    normal += normals[index.x] * coord.x;
    normal += normals[index.y] * coord.y;
    normal += normals[index.z] * coord.z;
    normal.w = 0.f;
    return normal;
}

glm::vec2 Mesh::sampleUV(const glm::uvec3 & index, const glm::vec3 & coord) {
    glm::vec2 uv;
    uv += uvs[index.x] * coord.x;
    uv += uvs[index.y] * coord.y;
    uv += uvs[index.z] * coord.z;
    return uv;
}

glm::vec4 Mesh::sampleColor(const glm::uvec3 & index, const glm::vec3 & coord) {
    // Since obj files do not support vertex colors, only check for textures
    if (material->hasTexture) {
        return material->sampleTexture(0, sampleUV(index, coord), glm::ivec2(0, 0));
    }
    else if (material->hasColor) {
        return material->maskColor;
    }
    else {
        return glm::vec4(1.f, 1.f, 1.f, 1.f);
    }
}

int Mesh::intersect(std::vector<Intersection> & results, const Ray & ray, bool recursive, int limit) {
    int count = 0;

    glm::vec4 newOrigin = worldTransformI * ray.origin;
    glm::vec4 newDirection = worldTransformI * ray.direction;
    float tScale = newDirection.length();
    Ray localRay(ray.depth, newOrigin, newDirection, ray.limits.x, ray.limits.y);

    FastStack<Accel *> accelStack;
    accelStack.push(accelStructure);

    while (!accelStack.empty()) {
        Accel * node = accelStack.top();
        accelStack.pop();
        if (node->boundingBox.intersects(localRay)) {
            if (node->isLeaf) {
                // Test faces
                for (int i = 0, l = node->indices.size(); i < l; i++) {
                    glm::vec4 result;
                    glm::uvec3 index = faces[node->indices[i]];
                    if (IntersectTriangle(result, localRay, positions[index.x], positions[index.y],
                            positions[index.z])) {
                        Intersection next(result.w / tScale, this, index, glm::vec3(result.x, result.y, result.z));
                        results.push_back(next);
                        count++;
                        if (limit > 0 && count >= limit) {
                            return count;
                        }
                    }
                }
            }
            else {
                // Add to stack
                for (int i = 0, l = node->children.size(); i < l; i++) {
                    accelStack.push(node->children[i]);
                }
            }
        }
    }

    if (recursive) {
        for (int i = 0; i < children.size(); i++) {
            count += children[i]->intersect(results, ray, recursive, limit);
            if (limit > 0 && count >= limit) {
                return count;
            }
        }
    }

    return count;
}
