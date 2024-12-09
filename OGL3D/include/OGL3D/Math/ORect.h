#pragma once
#include <OGL3D/OPrerequisites.h>

class ORect
{
public:
	ORect(){}                                                                                              //預設建構函數 | : 後的部分（例如 width(width) 和 height(height)）是初始化列表
	ORect(i32 width, i32 height) :width(width), height(height) {}                                          //初始化類別內的 width 和 height 成員
	ORect(i32 left, i32 top, i32 width, i32 height) :left(left),top(top), width(width), height(height) {}  //初始化類別內的 left, top, width, 和 height成員
	ORect(const ORect& rect) :left(rect.left), top(rect.top), width(rect.width), height(rect.height){}     //複製建構函數，另一個 ORect 物件 rect 來初始化當前物件
public:
	i32 width = 0, height = 0, left = 0, top = 0;
};