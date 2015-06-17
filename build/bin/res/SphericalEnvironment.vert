#version 330 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec4 inColor;

out vec4 outPosition;

uniform vec3 vViewport;
uniform mat4 mView;

void main() {
	float ratio = vViewport.y / vViewport.x;
	float s = tan(radians(vViewport.z / 2.0));
	float t = s * ratio;
	
    outPosition = mView * vec4(inPosition.x * s, inPosition.y * t, 1.0, 0.0);
	
    gl_Position = vec4(inPosition.xy, 0.99999, 1.0);
}
