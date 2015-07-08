#version 330 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 2) in vec2 inUV;

out vec4 outPosition;
out vec4 outNormal;
out vec2 outUV;

uniform mat4 mProjectionView;
uniform mat4 mTransform;
uniform mat4 mTransformIT;

void main() {
    outPosition = mTransform * inPosition;
    gl_Position = mProjectionView * outPosition;

    outNormal = mTransformIT * normalize(inNormal);
    outUV = inUV;
}
