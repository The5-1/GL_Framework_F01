#version 450

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout(location = 0) in vec3 aPosition; 

out vec3 vPosW;

void main() {

	vPosW =  (modelMatrix * vec4(aPosition, 1.0)).xyz;

	gl_Position = projMatrix * viewMatrix * vec4(vPosW, 1.0);
}

