#version 330 core

uniform sampler2D sTexture0;

uniform int iLightCount;
uniform vec4 vLightPosition[8];
uniform vec4 vLightColor[8];

in vec4 outPosition;
in vec4 outNormal;
in vec2 outUV;

out vec4 color;

void main() {
	vec3 V = outPosition.xyz;
    vec3 N = normalize(outNormal.xyz);
	
	vec4 totalColor = vec4(0.0, 0.0, 0.0, 1.0);
	for (int i = 0; i < iLightCount; i++) {
		// Test for directional lights
		vec4 l = vLightPosition[i];
		vec3 dir = l.xyz - V * l.w;
		float r = length(dir);
		float a = max(dot(normalize(dir), N), 0.0);
		
		totalColor.rgb += 4.0 / (r * r) * vLightColor[i].xyz * a;
	}
	
	vec4 texColor = texture2D(sTexture0, outUV.st);
	
    color = totalColor * texColor;
}
