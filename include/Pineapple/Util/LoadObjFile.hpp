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
 * @param filename      Path to the file
 * @param foldername    Path to the folder containing the file
 */
std::vector<Object3d *> LoadObjFile(const char * filename, const char * foldername = NULL);

#endif

