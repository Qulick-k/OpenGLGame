#include <OGL3D/Window/OWindow.h>  //�`�N�׽u��V�A���M�}���F�ɮ�
#include <Windows.h>               //�ϥ�Win32 API
#include <assert.h> 			   //�ϥ�assert��ơA�u�Ω�}�o���աA�� assert �������󬰰��ɡA�{���|��ܿ��~�T���ä������

OWindow::OWindow()
{ 
	WNDCLASSEX wc = {};                              //�Ыئ۩w�q�������]�Ҧp���ε{�������ιϧάɭ��^
	wc.cbSize = sizeof(WNDCLASSEX);                  //��l�� WNDCLASSEX ���c�骺 cbSize �����A�ë��w���c�骺�j�p
	wc.lpszClassName = L"OGL3DWindow";			     //���w�������O�W��
	wc.lpfnWndProc = DefWindowProc;                  //���w�����B�z��� DefWindowProc�t�d�����̤p�ơB�̤j�ơB�����FlpfnWndProc�B�z�o�e�쵡�f�������A�p�����J�B�ƹ��ƥ�Bø�s�ШD

	RegisterClassEx(&wc);                            //���U�������O wc�w�g�w�q�M��l�ƪ�WNDCLASSEX�ܼơA�]�t�������O���ݩʡA�Ҧp(lpfnWndProc)�B(lpszClassName)�B(hIcon)
}

OWindow::~OWindow()
{
}
