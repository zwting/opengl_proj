#version 330 core

out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

// lights
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

uniform vec3 camPos;


const int LIGHT_COUNT = 4;

#define saturate(v) clamp(v, 0, 1)
#define PI 3.1415926


vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(saturate(1.0 - cosTheta), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = saturate(dot(N, H));
	float NdotH2 = NdotH * NdotH;
	float denom = NdotH2 * (a2 - 1.0) + 1.0;
	denom = PI * denom * denom;

	return a2 / denom;
}

float GemoetrySchlickGGX(float NdotV, float k)
{
	float nom = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float k)
{
	float NdotV = saturate(dot(N, V));
	float NdotL = saturate(dot(N, L));
	float ggx1 = GemoetrySchlickGGX(NdotV, k);
	float ggx2 = GemoetrySchlickGGX(NdotL, k);

	return ggx1 * ggx2;
}

void main()
{

	vec3 N = normalize(Normal);
	vec3 V = normalize(camPos - WorldPos);

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);

	vec3 Lo = vec3(0.0);
	for(int i = 0; i < LIGHT_COUNT; ++i)
	{
		vec3 lightDir = lightPositions[i] - WorldPos;
		vec3 L = normalize(lightDir);
		vec3 H = normalize(L + V);

		float distance = length(lightDir);
		float attenuation = 1.0 / (distance * distance);
		vec3 radiance = lightColors[i] * attenuation;

		float NDF = DistributionGGX(N, H, roughness);
		float G = GeometrySmith(N, V, L, roughness);
		vec3 F = FresnelSchlick(saturate(dot(H, V)), F0);

		vec3 Ks = F;
		vec3 Kd = vec3(1.0) - Ks;
		Kd *= 1.0 - metallic;

		vec3 numerator = NDF * G * F;
		float denominator = 4.0 * saturate(dot(N, V)) * saturate(dot(N, L));
		vec3 specular = numerator / denominator;

		float NdotL = saturate(dot(N, L));
		Lo += (Kd * albedo / PI + specular) * radiance * NdotL;
	}

	vec3 ambient = vec3(0.03) * albedo * ao;
	vec3 color = ambient + Lo;

	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0 / 2.2));

	FragColor = vec4(color, 1.0);

}