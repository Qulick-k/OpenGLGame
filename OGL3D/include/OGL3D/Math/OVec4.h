#pragma once
#include <OGL3D/OPrerequisites.h>


class OVec4
{
public:
	OVec4()
	{

	}
	OVec4(f32 x, f32 y, f32 z, f32 w): x(x), y(y), z(z), w(w)        //定義一個類別或結構的建構函式（constructor），用於初始化類別或結構的成員變數。
	{

	}	
public:
	f32 x = 0, y = 0, z = 0, w = 0;                                  //RGBA分量
};
