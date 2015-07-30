#include "Pineapple/RenderBuffer.hpp"

RenderBuffer::RenderBuffer(int inWidth, int inHeight, float * inBuffer) :
        width(inWidth), height(inHeight), buffer(inBuffer) {
}

RenderBuffer::~RenderBuffer() {

}
