#version 450
  
in vec3 vPosW;

layout(location = 0)  out vec4 fragColor0;

vec3 makeGrid(vec3 pos, float thickness)
{
    return clamp(abs(fract(pos)*2.0-1.0)*thickness-thickness+2.0,0.0,1.0);
}

vec3 makeGrid2(vec3 pos, float thickness)
{
    float X = clamp(abs(fract(pos.y)*2.0-1.0)*abs(fract(pos.z)*2.0-1.0)*thickness-thickness+2.0,0.0,1.0);
    float Y = clamp(abs(fract(pos.x)*2.0-1.0)*abs(fract(pos.z)*2.0-1.0)*thickness-thickness+2.0,0.0,1.0);
    float Z = clamp(abs(fract(pos.x)*2.0-1.0)*abs(fract(pos.y)*2.0-1.0)*thickness-thickness+2.0,0.0,1.0);

    return vec3(X,Y,Z);
}

void main() 
{ 
    float thickness = gl_FragCoord.z*gl_FragCoord.w*500.0;
    vec3 grid = makeGrid2(vPosW,thickness);
    grid += makeGrid2(vPosW*2.0,thickness*0.5)*0.5;
    grid += makeGrid2(vPosW*10.0,thickness*0.1)*0.25;

#define GRIDTYPE 1
#if GRIDTYPE == 1
	fragColor0 = vec4(grid, 1.0);
#elif GRIDTYPE == 2
	fragColor0 = vec4(grid*grid.r*grid.g*grid.b, 1.0);
#endif

	//fragColor0 = vec4(makeGrid2(vPosW,thickness), 1.0);
}

