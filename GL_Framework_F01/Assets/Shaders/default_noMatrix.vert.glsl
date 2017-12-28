#version 450

layout(location = 0) in vec3 aPosition; 

out vec3 vPosW;

void main() {
	vPosW =  aPosition.xyz;
	gl_Position = vec4(vPosW, 1.0);
}

