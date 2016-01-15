#include "Pineapple/RenderTask.hpp"

int RenderTask::generateId = 1;

RenderTask::RenderTask(int inWidth, int inHeight, int inX, int inY, int inSamples, int inSeed) :
        width(inWidth), height(inHeight), x(inX), y(inY), samples(inSamples), data(new float[inWidth * inHeight * 4]), id(RenderTask::generateId++), seed(inSeed) {

}

RenderTask::~RenderTask() {

}
