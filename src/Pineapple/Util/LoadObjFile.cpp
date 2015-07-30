#include "Pineapple/Util/LoadObjFile.hpp"

#include "Pineapple/Object3d.hpp"
#include "Pineapple/Shape/Mesh.hpp"
#include "Pineapple/Material.hpp"

std::vector<Object3d *> LoadObjFile(const char * filename, const char * foldername) {
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err = tinyobj::LoadObj(shapes, materials, filename, foldername);

    std::vector<Object3d *> objects;

    if (!err.empty()) {
        printf("%s\n", err.c_str());
    }
    else {
        for (int i = 0, l = shapes.size(); i < l; i++) {
            tinyobj::mesh_t shape = shapes[i].mesh;
            Mesh * m;
            Material * mat;

            // Assume one material
            // TODO Multiple materials (?)
            if (shape.material_ids.size() > 0 && shape.material_ids[0] < materials.size()) {
                std::map<std::string, std::string> parameters = materials[shape.material_ids[0]].unknown_parameter;
                if (parameters.find("type") != parameters.end()) {
                    std::string type = parameters["type"];

                    mat = Material::getMaterial(type, parameters);
                }
                else { // Otherwise use a default material
                    mat = new Material(parameters);
                }
            }
            else {
                // Default material will be used
                mat = new Material();
            }
            m = new Mesh(mat);

            int indices = shape.indices.size();
            if (indices % 3 != 0) {
                continue;
            }
            for (int j = 0; j < indices; j += 3) {
                m->faces.push_back(glm::uvec3(shape.indices[j], shape.indices[j + 1], shape.indices[j + 2]));
            }
            m->faceCount = indices / 3;

            int positions = shape.positions.size();
            if (positions % 3 != 0) {
                continue;
            }
            for (int j = 0; j < positions; j += 3) {
                m->positions.push_back(
                        glm::vec4(shape.positions[j], shape.positions[j + 1], shape.positions[j + 2], 1.f));
            }
            m->vertexCount = positions / 3;

            int normals = shape.normals.size();
            if (normals % 3 != 0) {
                continue;
            }
            for (int j = 0; j < normals; j += 3) {
                m->normals.push_back(glm::vec4(shape.normals[j], shape.normals[j + 1], shape.normals[j + 2], 0.f));
            }

            int uvs = shape.texcoords.size();
            if (uvs % 2 != 0) {
                continue;
            }
            for (int j = 0; j < uvs; j += 2) {
                m->uvs.push_back(glm::vec2(shape.texcoords[j], shape.texcoords[j + 1]));
            }

            m->fillDefault();

            objects.push_back(m);
        }
    }

    return objects;
}
