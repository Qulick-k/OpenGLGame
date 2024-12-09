#pragma once
#include <OGL3D/Math/ORect.h>


class OWindow
{
	//add constructor and destructor
public:
	OWindow();  // �c�y����n��
	~OWindow(); // �R�c����n��

	ORect getInnerSize();       //�s�WgetInnerSize��ơA�Ω����Viewport�����j�p

	void makeCurrentContext();  //�s�WmakeCurrentContext��ơA�Ω�]�m��e�W�U��
	void present(bool vsync);   //�s�Wpresent��ơA�Ω�e�{�e��
	//void onDestroy();  //�s�WonDestroy��ơA�Ω�P������
	//bool isClosed();   //�s�WisClosed��ơA�Ω�P�_�����O�_����
private:
	void* m_handle = nullptr;  //�w�q�p�������ܼơA�x�s�귽���q�Ϋ��w
	void* m_context = nullptr; //�w�q�p�������ܼơA�x�s�W�U�媺�q�Ϋ��w
};

