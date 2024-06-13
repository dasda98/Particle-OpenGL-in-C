#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 particleColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = view * projection * vec4(aPos, 1.0);
    particleColor = aColor;
}