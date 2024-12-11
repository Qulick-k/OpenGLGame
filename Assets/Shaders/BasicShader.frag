#version 410 core

layout(location = 0) in vec3 inColor;


layout(location = 0) out vect4 outColor;


void main()
{
	outColor = vect4(0,0,1,1);
	outColor.rgb = inColor;
}
