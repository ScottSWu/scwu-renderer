#include "Pineapple/Material.hpp"

Material::Material() {
    
}

Material::~Material() {

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

glm::vec4 Material::sampleTexture(int texture, glm::vec2 uv, glm::uvec2 edge) {
    FIBITMAP * image = textures[texture];
    if (image == 0) {
        return glm::vec4();
    }
    else {
        int width = FreeImage_GetWidth(image);
        int height = FreeImage_GetHeight(image);
        glm::vec2 trueCoord = glm::vec2(width * uv.x, height * uv.y);
        glm::vec4 totalColor = glm::vec4();

        glm::uvec2 coord;
        float dx, dy, weight;

        coord = glm::uvec2((int) (width * uv.x), (int) (height * uv.y));
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

glm::vec4 Material::getPixel(FIBITMAP * image, int width, int height, glm::uvec2 coord, glm::uvec2 edge) {
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
