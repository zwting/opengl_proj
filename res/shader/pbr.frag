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
	

}