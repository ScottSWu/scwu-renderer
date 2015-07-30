#ifndef _Pineapple_Util_LoadJSON
#define _Pineapple_Util_LoadJSON

class Scene;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <json/json.h>

#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

/**
 * Load a JSON file.
 *
 * @param scene         Reference to the scene object to add to
 * @param filename      Path to the file
 * @param foldername    Path to the folder containing the file
 */
void LoadJSONFile(Scene * scene, const char * filename, const char * foldername = NULL);

#endif
