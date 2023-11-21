#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;


out vec3 crntPos;
out vec3 Normal;
out vec3 color;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 rotation;

uniform vec3 inColor;

void main()
{
	Normal = vec3(rotation * vec4(aNormal, 1.0));
	color = inColor;
	
	gl_Position = camMatrix * model * vec4(aPos, 1.0);
}