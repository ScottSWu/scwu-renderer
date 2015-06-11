#version 330 core

in vec4 outPosition;
in vec4 outNormal;
in vec4 outColor;

out vec4 color;

void main() {
    vec3 N = normalize(outNormal.xyz);
    vec3 L = normalize(vec3(1.0, 1.0, 1.0));

    color = outColor;// * max(dot(N, L), 0.0);
}
