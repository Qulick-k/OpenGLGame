#pragma once
class OWindow
{
	//add constructor and destructor
public:
	OWindow();  // �c�y����n��
	~OWindow(); // �R�c����n��

	void onDestroy();  //�s�WonDestroy��ơA�Ω�P������
	bool isClosed();   //�s�WisClosed��ơA�Ω�P�_�����O�_����
private:
	void* m_handle = nullptr;  //�w�q�p�������ܼơA�x�s�귽���q�Ϋ��w
};

