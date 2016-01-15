#ifndef _Pineapple_Util_Sampler
#define _Pineapple_Util_Sampler

#include <math.h>
#include <stdlib.h>
#include <glm/glm.hpp>

#include "Pineapple/Globals.hpp"

/**
 * A collection of sampling functions.
 */

/**
 * Seed the random number generator.
 *
 * @param seed      Seed used for the random number generator
 */
void SampleSeed(int);

/**
 * @return  A random sign (-1 or 1).
 */
float SampleSign();

/**
 * @param n     Upper bound for sample
 * @return  A random integer from 0 to n (exclusive)
 */
int SampleInt(int n = RAND_MAX);

/**
 * @return  A random float between 0 and 1 (exclusive)
 */
float SampleUniform();

/**
 * @return  A random vector from a unit sphere
 */
glm::vec4 SampleSphere();

/**
 * @param dir   The normal of the plane containing the base of the hemisphere
 * @return  A random vector from a unit hemisphere in a direction
 */
glm::vec4 SampleHemi(glm::vec4);

#endif
