#include "Pineapple/Util/Sampler.hpp"

void SampleSeed(int seed) {
    srand(seed);
}

float SampleSign() {
    return (rand() & 1) * 2 - 1.f;
}

int SampleInt(int n) {
    return rand() % n;
}

float SampleUniform() {
    return rand() / float(RAND_MAX);
}

glm::vec4 SampleSphere() {
    float r = sqrt(SampleUniform());
    float t = SampleUniform() * 2.f * PAC_PI;
    float x = r * cos(t);
    float y = r * sin(t);
    float z = SampleSign() * sqrt(1.f - x * x - y * y);
    return glm::vec4(x, y, z, 0.f);
}

glm::vec4 SampleHemi(glm::vec4 dir = glm::vec4(0.f, 1.f, 0.f, 0.f)) {
    glm::vec4 s = SampleSphere();
    float dp = glm::dot(s, dir);
    if (dp < 0) {
        s = s - 2.f * dp * dir;
    }
    return s;
}
