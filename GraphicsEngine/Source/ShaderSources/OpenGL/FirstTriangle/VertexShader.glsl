#version 430 core
layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec3 vColor;

out vec3 iColor;
void main()
 {
	iColor = vColor;
	gl_Position = vec4(vPosition , 1 , 1);
 }