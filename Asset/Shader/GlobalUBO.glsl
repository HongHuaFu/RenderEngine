#ifndef GLOBAOL_UBO_GLSL
#define GLOBAOL_UBO_GLSL

layout (std140, binding = 0) uniform Global
{
    mat4 projection;
    mat4 view;
    vec4 camPos;
};

#endif