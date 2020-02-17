#version 450 core

uniform mat4x4 matModelView;
uniform mat4x4 matProjection;

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

flat out vec4 outColor;
 
void main()
{
	vec4 eyePos = matModelView * vPosition;
    gl_Position = matProjection * eyePos;

	outColor = vColor;

	float dist = length(eyePos.xyz);
	float att = sqrt(0.01f*dist);
	gl_PointSize = 20.0f * att;
}