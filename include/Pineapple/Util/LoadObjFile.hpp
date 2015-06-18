#ifndef _Pineapple_Util_LoadObj
#define _Pineapple_Util_LoadObj

#include <tiny_obj_loader.h>

#include <vector>
#include <string>
#include <stdio.h>

#include "Pineapple/Object3d.hpp"
#include "Pineapple/Shape/Mesh.hpp"

/**
 * Load an obj file
 *
 * @param filename  Path to the file
 */
std::vector<Object3d *> LoadObjFile(char filename[], char foldername[] = NULL);

#endif

