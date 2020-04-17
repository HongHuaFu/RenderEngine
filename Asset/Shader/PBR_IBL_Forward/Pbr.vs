

#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoords;
out vec3 WorldPos;
out vec3 WorldNormal;

#include "../GlobalUBO.glsl"

uniform mat4 model;

void main()
{
    TexCoords = aTexCoords.x;

    WorldPos = vec3(model * vec4(aPos, 1.0));
    WorldNormal = mat3(model) * aNormal;   

    gl_Position =  projection * view * vec4(WorldPos, 1.0);
}