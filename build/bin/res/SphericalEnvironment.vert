#version 330 core

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec4 inColor;

out vec3 outPosition;

uniform vec3 vViewport;
uniform vec3 vCameraDirection;
uniform mat4 mProjectionView;

void main() {
	float ratio = vViewport.y / vViewport.x;
	float s = tan(radians(vViewport.z / 2.0));
	float t = s * ratio;
	
	vec3 viewDir = vCameraDirection;
	float theta = -atan(viewDir.z, viewDir.x);
	float phi = -atan(viewDir.y, sqrt(viewDir.x * viewDir.x + viewDir.z * viewDir.z));
	
	viewDir.x = cos(phi) * cos(theta);
	viewDir.y = sin(phi);
	viewDir.z = cos(phi) * sin(theta);
	
	vec3 right = cross(viewDir, vec3(0.0, 1.0, 0.0));
	vec3 up = cross(right, viewDir);
	
	outPosition = viewDir + right * s * inPosition.x + up * t * inPosition.y;
	
    gl_Position = vec4(inPosition.xy, 0.99999, 1.0);
	//gl_Position = mProjectionView * vec4(outPosition, 1.0);
}
