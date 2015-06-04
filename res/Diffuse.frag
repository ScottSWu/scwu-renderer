#version 330 core

in vec4 outPosition;
in vec4 outNormal;

out vec4 color;

void main() {
    vec3 N = normalize(outNormal).xyz;
    vec3 L = normalize(vec3(1.0, 1.0, 1.0));

    color = vec4(1.0, 1.0, 1.0, 1.0) * max(dot(N, L), 0.0);
}
