#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;

out vec4 outPosition;
out vec4 outNormal;

uniform mat4 mViewProjection;
uniform mat4 mTransform;
uniform mat4 mTransformIT;

void main() {
    outPosition = mTransform * vec4(inPosition, 1.0);
    gl_Position = mViewProjection * outPosition;

    outNormal = mTransformIT * normalize(vec4(inNormal, 0.0));
}
