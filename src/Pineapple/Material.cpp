#include "Pineapple/Material.hpp"

#include "Pineapple/Intersection.hpp"
#include "Pineapple/Material/DiffuseMaterial.hpp"
#include "Pineapple/Material/GlassMaterial.hpp"
#include "Pineapple/Ray.hpp"
#include "Pineapple/Scene.hpp"

Material::Material(std::map<std::string, std::string> parameters) :
        hasTexture(false), hasColor(false), maskColor(glm::vec4(1.f, 1.f, 1.f, 1.f)) {
    // Set properties
    for (auto itr = parameters.begin(), itrEnd = parameters.end(); itr != itrEnd; itr++) {
        properties[itr->first.c_str()] = itr->second.c_str();
    }

    if (properties.find("color") != properties.end()) {
        std::stringstream ss(properties["color"]);
        std::string component;
        std::vector<std::string> components;
        while (std::getline(ss, component, ' ')) {
            components.push_back(component);
        }

        glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f);
        switch (components.size()) {
            case 4:
                color.a = std::atof(components[3].c_str());
                // No break
            case 3:
                color.r = std::atof(components[0].c_str());
                color.g = std::atof(components[1].c_str());
                color.b = std::atof(components[2].c_str());
                break;
            case 2:
                color.a = std::atof(components[1].c_str());
                // No break
            case 1:
                color.r = std::atof(components[0].c_str());
                color.g = std::atof(components[0].c_str());
                color.b = std::atof(components[0].c_str());
                break;
            default:
                break;
        }

        hasColor = true;
        maskColor = color;
    }
}

Material::~Material() {

}

Material * Material::getMaterial(std::string type, std::map<std::string, std::string> parameters) {
    if (type == "diffuse") {
        return new DiffuseMaterial(parameters);
    }
    else if (type == "glass") {
        return new GlassMaterial(parameters);
    }
    else {
        return new Material(parameters);
    }
}

void Material::loadTextures() {
    // Unload all current textures
    for (std::vector<FIBITMAP *>::iterator i = textures.begin(); i != textures.end(); i++) {
        FreeImage_Unload(*i);
    }
    textures.clear();

    // Load up to 8 textures in properties
    std::map<std::string, std::string>::const_iterator searchTexture;
    std::string tname;
    for (char i = '0'; i < '8'; i++) {
        tname = "texture";
        tname += i;
        searchTexture = properties.find(tname);
        if (searchTexture != properties.end()) {
            textures.push_back(loadImage(searchTexture->second.c_str()));
        }
        else {
            break;
        }
    }

    if (textures.size() > 0) {
        hasTexture = true;
    }
}

FIBITMAP * Material::loadImage(const char * filename) {
    printf("Loading texture \'%s\'\n", filename);

    FREE_IMAGE_FORMAT imageFormat = FIF_UNKNOWN;
    FIBITMAP * image(0);
    BYTE * data(0);
    int width = 0;
    int height = 0;

    // Get image format
    imageFormat = FreeImage_GetFileType(filename, 0);
    if (imageFormat == FIF_UNKNOWN) {
        imageFormat = FreeImage_GetFIFFromFilename(filename);
    }
    if (imageFormat == FIF_UNKNOWN) { // Give up
        printf("\tUnknown image format\n");
        return 0;
    }

    if (FreeImage_FIFSupportsReading(imageFormat)) {
        image = FreeImage_Load(imageFormat, filename);
    }
    else {
        printf("\tUnsupported image format\n");
    }
    if (!image) {
        FreeImage_Unload(image);
        printf("\tCould not load file\n");
        return 0;
    }

    // Get image data
    data = FreeImage_GetBits(image);
    width = FreeImage_GetWidth(image);
    height = FreeImage_GetHeight(image);

    if ((data == 0) || (width == 0) || (height == 0)) {
        FreeImage_Unload(image);
        printf("\tFailed to read file\n");
        return 0;
    }

    return image;
}

glm::vec4 Material::sampleTexture(int texture, glm::vec2 uv, glm::ivec2 edge) {
    FIBITMAP * image = textures[texture];
    if (image == 0) {
        return glm::vec4();
    }
    else {
        int width = FreeImage_GetWidth(image);
        int height = FreeImage_GetHeight(image);
        glm::vec2 trueCoord = glm::vec2(width * uv.x, height * uv.y);
        glm::vec4 totalColor = glm::vec4();

        glm::ivec2 coord;
        float dx, dy, weight;

        coord = glm::ivec2((int) (width * uv.x), (int) (height * uv.y));
        dx = trueCoord.x - coord.x;
        dy = trueCoord.y - coord.y;
        weight = (1.f - dx) * (1.f - dy);
        totalColor += weight * getPixel(image, width, height, coord, edge);

        coord.x = coord.x + 1;
        weight = dx * (1.f - dy);
        totalColor += weight * getPixel(image, width, height, coord, edge);

        coord.y = coord.y + 1;
        weight = dx * dy;
        totalColor += weight * getPixel(image, width, height, coord, edge);

        coord.x = coord.x - 1;
        weight = (1.f - dx) * dy;
        totalColor += weight * getPixel(image, width, height, coord, edge);

        return totalColor;
    }
}

glm::vec4 Material::getPixel(FIBITMAP * image, int width, int height, glm::ivec2 coord, glm::ivec2 edge) {
    switch (edge.x) {
        default:
        case -1:
            if (coord.x < 0 || coord.x >= width) {
                return glm::vec4(0.f, 0.f, 0.f, 1.f);
            }
            break;
        case 0:
            if (coord.x < 0) {
                coord.x = 0;
            }
            else if (coord.x >= width) {
                coord.x = width - 1;
            }
            break;
        case 1:
            coord.x = coord.x % width;
            if (coord.x < 0) {
                coord.x = coord.x + width;
            }
            break;
    }
    switch (edge.y) {
        default:
        case -1:
            if (coord.y < 0 || coord.y >= height) {
                return glm::vec4(0.f, 0.f, 0.f, 1.f);
            }
            break;
        case 0:
            if (coord.y < 0) {
                coord.y = 0;
            }
            else if (coord.y >= height) {
                coord.y = height - 1;
            }
            break;
        case 1:
            coord.y = coord.y % height;
            if (coord.y < 0) {
                coord.y = coord.y + height;
            }
            break;
    }

    RGBQUAD color;
    FreeImage_GetPixelColor(image, coord.x, coord.y, &color);
    return glm::vec4((float) color.rgbRed / 255.f, (float) color.rgbGreen / 255.f, (float) color.rgbBlue / 255.f, 1.f);
}

glm::vec4 Material::sampleColor(FastStack<Ray> & rays, const Ray ray, const Intersection & result,
        Scene * scene) {
    auto itrEnd = properties.end();
    if (hasTexture) {
        glm::vec2 uv = result.surface->sampleUV(result.index, result.coord);
        return sampleTexture(0, uv, glm::ivec2(0, 0));
    }
    else if (hasColor) {
        return maskColor;
    }
    else {
        return glm::vec4(1.f, 1.f, 1.f, 1.f);
    }
}
