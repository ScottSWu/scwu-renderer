#include "Pineapple/Util/LoadJSONFile.hpp"

#include "Pineapple/Camera/PerspectiveCamera.hpp"
#include "Pineapple/Camera/OrthographicCamera.hpp"
#include "Pineapple/Light/DirectionalLight.hpp"
#include "Pineapple/Light/PointLight.hpp"
#include "Pineapple/Object3d.hpp"
#include "Pineapple/Scene.hpp"
#include "Pineapple/Util/LoadObjFile.hpp"

void LoadJSONFile(Scene * scene, const char * filename, const char * foldername) {
    std::ifstream fin(filename);

    // Root value
    Json::Value root;

    Json::Reader reader(Json::Features::all());
    bool parsingSuccessful = reader.parse(fin, root);

    // Parse failure
    if (!parsingSuccessful) {
        return;
    }

    // Read scene
    if (root["camera"] != Json::nullValue) {
        Json::Value camera = root["camera"];
        glm::vec3 position = glm::vec3(0.f, 0.f, 1.f);
        glm::vec3 target = glm::vec3(0.f, 0.f, 0.f);
        glm::ivec2 viewport = glm::ivec2(320, 320);
        glm::vec2 planes = glm::vec2(0.1f, 100.f);

        if (camera["position"] != Json::nullValue) {
            Json::Value p = camera["position"];
            position.x = p[0].asFloat();
            position.y = p[1].asFloat();
            position.z = p[2].asFloat();
        }
        if (camera["target"] != Json::nullValue) {
            Json::Value t = camera["target"];
            target.x = t[0].asFloat();
            target.y = t[1].asFloat();
            target.z = t[2].asFloat();
        }

        if (camera["width"] != Json::nullValue) {
            viewport.x = camera["width"].asInt();
        }
        if (camera["height"] != Json::nullValue) {
            viewport.y = camera["height"].asInt();
        }

        if (camera["near"] != Json::nullValue) {
            planes.x = camera["near"].asFloat();
        }
        if (camera["far"] != Json::nullValue) {
            planes.y = camera["far"].asFloat();
        }

        std::string type = camera["type"].asString();
        if (type == "perspective") {
            float fov = 45.f;
            if (camera["fov"] != Json::nullValue) {
                fov = camera["fov"].asFloat();
            }
            Camera * newCamera = new PerspectiveCamera(fov);
            scene->setCamera(newCamera);
        }
        else if (type == "orthographic") {
            glm::vec4 bounds = glm::vec4(-1.f, 1.f, 1.f, -1.f);
            if (camera["bounds"] != Json::nullValue) {
                Json::Value b = camera["bounds"];
                bounds.x = b[0].asFloat();
                bounds.y = b[1].asFloat();
                bounds.z = b[2].asFloat();
                bounds.w = b[3].asFloat();
            }
            Camera * newCamera = new OrthographicCamera(bounds.x, bounds.y, bounds.z, bounds.w);
            scene->setCamera(newCamera);
        }

        scene->setCameraPosition(position.x, position.y, position.z);
        scene->setCameraTarget(target.x, target.y, target.z);
        scene->setCameraViewport(viewport.x, viewport.y);
        scene->setCameraPlanes(planes.x, planes.y);
    }

    if (root["lights"] != Json::nullValue) {
        Json::Value lights = root["lights"];
        scene->removeAllLights();
        for (int i = 0, l = lights.size(); i < l; i++) {
            Json::Value light = lights[i];

            glm::vec4 position = glm::vec4(0.f, 0.f, 0.f, 1.f);
            glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f);

            if (light["position"] != Json::nullValue) {
                Json::Value p = light["position"];
                position.x = p[0].asFloat();
                position.y = p[1].asFloat();
                position.z = p[2].asFloat();
            }
            if (light["color"] != Json::nullValue) {
                Json::Value c = light["color"];
                color.x = c[0].asFloat();
                color.y = c[1].asFloat();
                color.z = c[2].asFloat();
            }

            std::string type = light["type"].asString();
            if (type == "directional") {
                scene->addLight(new DirectionalLight(position, color));
            }
            else {
                float intensity = 1.f;
                if (light["intensity"] != Json::nullValue) {
                    intensity = light["intensity"].asFloat();
                }
                scene->addLight(new PointLight(position, color, intensity));
            }
        }
    }

    if (root["children"] != Json::nullValue) {
        Json::Value children = root["children"];
        for (int i = 0, l = children.size(); i < l; i++) {
            Json::Value child = children[i];
            std::string type = child["type"].asString();

            glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);
            glm::vec3 scale = glm::vec3(1.f, 1.f, 1.f);
            glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f);

            if (child["position"] != Json::nullValue) {
                Json::Value p = child["position"];
                position.x = p[0].asFloat();
                position.y = p[1].asFloat();
                position.z = p[2].asFloat();
            }
            if (child["scale"] != Json::nullValue) {
                Json::Value s = child["scale"];
                scale.x = s[0].asFloat();
                scale.y = s[1].asFloat();
                scale.z = s[2].asFloat();
            }
            if (child["rotation"] != Json::nullValue) {
                Json::Value r = child["rotation"];
                rotation.x = r[0].asFloat();
                rotation.y = r[1].asFloat();
                rotation.z = r[2].asFloat();
            }

            glm::mat4 transform = glm::mat4();
            transform = glm::translate(transform, position);
            transform = glm::scale(transform, scale);
            transform = glm::rotate(transform, rotation.y, glm::vec3(0.f, 1.f, 0.f));
            transform = glm::rotate(transform, rotation.x, glm::vec3(1.f, 0.f, 0.f));
            transform = glm::rotate(transform, rotation.z, glm::vec3(0.f, 0.f, 1.f));

            if (type == "mesh") {
                if (child["file"] != Json::nullValue) {
                    std::string filePath = child["file"].asString();
                    int j = filePath.rfind("\\");
                    if (j < 0) {
                        j = filePath.rfind("/");
                    }
                    std::string folderPath = (j < 0) ? "./" : filePath.substr(0, j + 1);

                    std::vector<Object3d *> objects = LoadObjFile(filePath.c_str(), folderPath.c_str());

                    for (auto k = objects.begin(); k != objects.end(); k++) {
                        (*k)->transform = transform;
                        scene->addObject(*k);
                    }
                }
            }
            // TODO Primitives
        }
    }
}
