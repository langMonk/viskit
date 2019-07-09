#version 450 core

layout (location = 0) out vec4 vFragColor;

uniform sampler2D tex;
flat in vec4 outColor;

void main(void)
{
	vFragColor = outColor * texture(tex, gl_PointCoord);
}