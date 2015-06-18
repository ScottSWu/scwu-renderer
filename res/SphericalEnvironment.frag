#version 330 core

#define M_PI2 1.57079632679
#define M_PI  3.14159265358
#define M_2PI 6.28318530718

uniform sampler2D sTexture0;

in vec3 outPosition;

out vec4 color;

void main() {
	float r = sqrt(outPosition.x * outPosition.x + outPosition.z * outPosition.z);
	float theta = atan(outPosition.z, outPosition.x);
	float phi = atan(outPosition.y, r);
	
	theta = theta / M_2PI + 0.5;
	phi = phi / M_PI + 0.5;
	
	color = texture2D(sTexture0, vec2(theta, phi)).bgra;
}
