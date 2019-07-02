#version 450

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 vColor;
 
void main()
{
  gl_Position = cameraToView * worldToCamera * modelToWorld * position;
  vColor = color;

  gl_PointSize = 10.0f;
}