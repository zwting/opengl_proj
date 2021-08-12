#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 model_inv;

void main()
{
    TexCoords = aTexCoords;
    WorldPos = vec3(model * vec4(aPos, 1.0));
    Normal = transpose(mat3(model_inv)) * aNormal;   
    //Normal = aNormal;

    gl_Position =  proj * view * vec4(WorldPos, 1.0);
}