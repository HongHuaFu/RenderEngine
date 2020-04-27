#version 460 core
layout (location = 0) in vec3 aPos;
out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;

    // 去除位移因素影响
    mat4 rotView = mat4(mat3(view));
    vec4 pos = projection * rotView * vec4(aPos, 1.0);

    // 将z替换为w 透视除法后 始终保证为最大深度1.0f
    gl_Position = pos.xyww;
}  