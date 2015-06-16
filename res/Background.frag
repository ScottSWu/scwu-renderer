#version 330 core

in vec4 outPosition;

out vec4 color;

void main() {
	float intensity = outPosition.y / 4 + 0.5;
    color = vec4(intensity, intensity, intensity, 1.0);
}
