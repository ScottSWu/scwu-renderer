#version 330 core

#define M_PI2 1.57079632679
#define M_PI  3.14159265358
#define M_2PI 6.28318530718

uniform sampler2D sTexture0;
uniform sampler2D sTexture1;
uniform sampler2D sTexture2;
uniform sampler2D sTexture3;
uniform sampler2D sTexture4;
uniform sampler2D sTexture5;

in vec3 outPosition;

out vec4 color;

void main() {
	vec3 dir = normalize(outPosition);
	vec3 mag = abs(outPosition);
	if (mag.x >= mag.y && mag.x >= mag.z) { // r-l 0-1
		dir = dir / mag.x / 2.0 + 0.5;
		if (dir.x >= 0.5) { // r 0
			color = texture2D(sTexture0, vec2(1.0 - dir.z, dir.y)).bgra;
		}
		else { // l 1
			color = texture2D(sTexture1, vec2(dir.z, dir.y)).bgra;
		}
	}
	else if (mag.y >= mag.x && mag.y >= mag.z) { // t-d 2-3
		dir = dir / mag.y / 2.0 + 0.5;
		if (dir.y >= 0.5) { // t 2
			color = texture2D(sTexture2, vec2(dir.x, 1.0 - dir.z)).bgra;
		}
		else { // d 3
			color = texture2D(sTexture3, vec2(dir.x, dir.z)).bgra;
		}
	}
	else if (mag.z >= mag.x && mag.z >= mag.y) { // f-b 4-5
		dir = dir / mag.z / 2.0 + 0.5;
		if (dir.z >= 0.5) { // f 4
			color = texture2D(sTexture4, vec2(dir.x, dir.y)).bgra;
		}
		else { // b 5
			color = texture2D(sTexture5, vec2(1.0 - dir.x, dir.y)).bgra;
		}
	}
	else {
		color = vec4(0.0, 0.0, 0.0, 1.0);
	}
}
