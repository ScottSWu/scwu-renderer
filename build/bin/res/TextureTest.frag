#version 330 core

uniform sampler2D sTexture0;

in vec4 outPosition;
in vec4 outNormal;
in vec2 outUV;

out vec4 color;

void main() {
    vec3 N = normalize(outNormal.xyz);
    vec3 L = normalize(vec3(2.0, 2.5, 1.5));
	
	vec4 texColor = texture2D(sTexture0, outUV.st);
	
    color = texColor;// * max(dot(N, L), 0.0);
}
