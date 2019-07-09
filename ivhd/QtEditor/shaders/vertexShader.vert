#version 450 core

//uniform mat4 modelToWorld;
//uniform mat4 worldToCamera;
//uniform mat4 cameraToView;

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

flat out vec4 outColor;
 
void main()
{
	gl_Position = vPosition;
	outColor = vColor;

	gl_PointSize = 20.0f;
}