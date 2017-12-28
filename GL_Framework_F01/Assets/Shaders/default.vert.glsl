#version 450

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

layout(location = 0) in vec3 aPosition; 

out vec3 vPosW;

void main() {

	vPosW =  (uModelMatrix * vec4(aPosition, 1.0)).xyz;

	gl_Position = uProjectionMatrix * uViewMatrix * vec4(vPosW, 1.0);
}

