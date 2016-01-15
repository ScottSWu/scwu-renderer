#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <unistd.h>
#include <glm/glm.hpp>
#include <FreeImage.h>

#include "Pineapple/Pineapple.hpp"
#include "Pineapple/Camera.hpp"
#include "Pineapple/Scene.hpp"
#include "Pineapple/Util/LoadJSONFile.hpp"

int main(int argc, char** argv) {
    char * fin;
    char * fout;
    std::string seed("0");
    std::string threads("1");
    std::string samples("100");

    int c;
    while ((c = getopt(argc, argv, "hj:s:r:i:o:")) != -1) {
        switch (c) {
            case 'i':
                fin = optarg;
                break;
            case 'o':
                fout = optarg;
                break;
            case 'j':
                threads = std::string(optarg);
                break;
            case 's':
                samples = std::string(optarg);
                break;
            case 'r':
                seed = std::string(optarg);
                break;
            case 'h':
            default:
                printf("Usage: ./Pineapple-cli.exe -i <input> -o <output>\n");
                printf("        -h      This help text\n");
                printf("        -j      Threads (default 1)\n");
                printf("        -s      Samples per pixel (default 100)\n");
                printf("        -r      Initial seed (default 0)\n");
                printf("        Latter two are required for now, TODO with getopt_long");
                return 1;
        }
    }

    Pineapple p;
    Scene * s = p.getScene();
    LoadJSONFile(s, fin);

    std::map<std::string, std::string> params;
    params["type"] = "pathtrace";
    params["cores"] = threads;
    params["samples"] = samples;
    params["seed"] = seed;
    p.setRenderer(params);

    // Render
    p.render();

    // Save image to output
    RenderBuffer * output = p.getRenderBuffer();

    int width = output->width;
    int height = output->height;
    float * imageBuffer = output->buffer;
    FIBITMAP * bitmap = FreeImage_Allocate(width, height, 32,
    FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK);
    if (bitmap) {
        // Clamp all values between 0 and 1
        for (int i = 0, l = width * height * 4; i < l; i++) {
            if (imageBuffer[i] < 0.f) {
                imageBuffer[i] = 0.f;
            }
            else if (imageBuffer[i] > 1.f) {
                imageBuffer[i] = 1.f;
            }
        }

        // Write to bitmap
        int offset = 0;
        for (int i = 0; i < height; i++) {
            BYTE * line = FreeImage_GetScanLine(bitmap, i);
            for (int j = 0; j < width; j++) {
                line[FI_RGBA_RED] = (int) (imageBuffer[offset + 0] * 255);
                line[FI_RGBA_GREEN] = (int) (imageBuffer[offset + 1] * 255);
                line[FI_RGBA_BLUE] = (int) (imageBuffer[offset + 2] * 255);
                //line[FI_RGBA_ALPHA] = (int) (imageBuffer[offset + 3] * 255);
                line[FI_RGBA_ALPHA] = 255;
                line += 4;
                offset += 4;
            }
        }

        // Save and clean up
        FreeImage_Save(FIF_PNG, bitmap, fout, 0);
    }
    FreeImage_Unload(bitmap);

    return 0;
}
