#version 450 core

layout (location = 0) out vec4 color;

uniform sampler2D tex;
flat in vec4 outColor;

void main(void)
{
	color = outColor * texture(tex, gl_PointCoord);
}