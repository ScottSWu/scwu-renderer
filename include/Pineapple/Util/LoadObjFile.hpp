#ifndef _Pineapple_Util_LoadObj
#define _Pineapple_Util_LoadObj

class Object3d;

#include <tiny_obj_loader.h>

#include <vector>
#include <string>
#include <stdio.h>

/**
 * Load an obj file
 *
 * @param filename  Path to the file
 */
std::vector<Object3d *> LoadObjFile(char filename[], char foldername[] = NULL);

#endif

