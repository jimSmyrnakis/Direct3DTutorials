#version 430 core
layout (location = 0) out vec4 fColor;
in vec3 iColor;
void main(){
	fColor = vec4(iColor, 1.0);
}