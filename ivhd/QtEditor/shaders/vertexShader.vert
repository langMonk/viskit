#version 450 core

uniform mat4x4 matModelview;
uniform mat4x4 matProjection;

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

flat out vec4 outColor;
 
void main()
{
	vec4 eyePos = matModelview * vPosition;
    gl_Position = matProjection * eyePos;

	outColor = vColor;

	float dist = length(eyePos.xyz);
	float att = inversesqrt(0.1f*dist);
	gl_PointSize = 2.0f * att;
}