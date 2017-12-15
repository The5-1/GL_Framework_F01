#version 450
  
in vec3 vPosW;

layout(location = 0)  out vec4 fragColor0;

void main() 
{ 
	fragColor0 = vec4(vPosW, 1.0);
}

