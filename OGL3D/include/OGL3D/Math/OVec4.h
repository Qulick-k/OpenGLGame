#pragma once
#include <OGL3D/OPrerequisites.h>


class OVec4
{
public:
	OVec4()
	{

	}
	OVec4(f32 x, f32 y, f32 z, f32 w): x(x), y(y), z(z), w(w)        //�w�q�@�����O�ε��c���غc�禡�]constructor�^�A�Ω��l�����O�ε��c�������ܼơC
	{

	}	
public:
	f32 x = 0, y = 0, z = 0, w = 0;                                  //RGBA���q
};
