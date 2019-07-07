#version 450

//uniform mat4 modelToWorld;
//uniform mat4 worldToCamera;
//uniform mat4 cameraToView;

layout(location = 0) in vec4 position;
//layout(location = 1) in vec4 color;

//out vec4 vColor;
 
void main()
{
  gl_Position = position;
  gl_PointSize = 20.0f;
}