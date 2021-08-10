#version 330 core

out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

uniform vec3 camPos;
uniform float metallic;
uniform float roughness;
uniform float ao;

const int LIGHT_COUNT = 4;
void main()
{

	vec3 N = normalize(Normal);
	vec3 V = normalize(camPos - WorldPos);

	vec3 Lo = vec3(0.0);
	for(int i = 0; i < LIGHT_COUNT; ++i)
	{
		vec3 L = normalize(lightPosition[i] - WorldPos);
		vec3 H = normalize(L + V);

		
	}

}