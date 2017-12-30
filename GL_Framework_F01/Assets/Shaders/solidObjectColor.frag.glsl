#version 450
uniform vec4 uObjectColor;

layout(location = 0)  out vec4 fragColor0;

void main() 
{ 
	fragColor0 = uObjectColor;
}

