#include "Pineapple/RenderTask.hpp"

RenderTask::RenderTask(int inWidth, int inHeight, int inX, int inY, int inSamples) :
        width(inWidth), height(inHeight), x(inX), y(inY), samples(inSamples), data(new float[inWidth * inHeight * 4]) {

}

RenderTask::~RenderTask() {

}
