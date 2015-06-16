#version 330 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec4 inColor;

out vec4 outPosition;

void main() {
    outPosition = inPosition;
    // TODO disable depth test instead?
    outPosition.z = 0.9999999;
    gl_Position = outPosition;
}
