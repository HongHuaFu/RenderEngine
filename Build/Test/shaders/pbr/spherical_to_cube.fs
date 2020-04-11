#version 430 core
out vec4 FragColor;
in vec3 WorldPos;

#include ../common/constants.glsl
#include ../common/sampling.glsl

uniform sampler2D environment;

void main()
{
	// 计算等距柱状体投影采样uv
	vec2 uv = SampleSphericalMap(normalize(WorldPos));
	vec3 color = texture(environment, uv).rgb;
    FragColor = vec4(color, 1.0);
}