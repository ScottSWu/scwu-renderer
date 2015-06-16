#version 330 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec4 inColor;

out vec4 outPosition;
out vec4 outNormal;
out vec4 outColor;

uniform mat4 mProjectionView;
uniform mat4 mTransform;
uniform mat4 mTransformIT;

void main() {
    outPosition = mTransform * inPosition;
    gl_Position = mProjectionView * outPosition;

    outNormal = mTransformIT * normalize(inNormal);
    outColor = inColor;
}
