#pragma once
#include <OGL3D/OPrerequisites.h>

class ORect
{
public:
	ORect(){}                                                                                              //�w�]�غc��� | : �᪺�����]�Ҧp width(width) �M height(height)�^�O��l�ƦC��
	ORect(i32 width, i32 height) :width(width), height(height) {}                                          //��l�����O���� width �M height ����
	ORect(i32 left, i32 top, i32 width, i32 height) :left(left),top(top), width(width), height(height) {}  //��l�����O���� left, top, width, �M height����
	ORect(const ORect& rect) :left(rect.left), top(rect.top), width(rect.width), height(rect.height){}     //�ƻs�غc��ơA�t�@�� ORect ���� rect �Ӫ�l�Ʒ�e����
public:
	i32 width = 0, height = 0, left = 0, top = 0;
};