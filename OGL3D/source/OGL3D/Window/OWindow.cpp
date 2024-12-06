#include <OGL3D/Window/OWindow.h>  //�`�N�׽u��V�A���M�}���F�ɮ�
#include <Windows.h>               //�ϥ�Win32 API
#include <assert.h> 			   //�ϥ�assert��ơA�u�Ω�}�o���աA�� assert �������󬰰��ɡA�{���|��ܿ��~�T���ä������

OWindow::OWindow()
{ 
	WNDCLASSEX wc = {};                              //�Ыئ۩w�q�������]�Ҧp���ε{�������ιϧάɭ��^
	wc.cbSize = sizeof(WNDCLASSEX);                  //��l�� WNDCLASSEX ���c�骺 cbSize �����A�ë��w���c�骺�j�p
	wc.lpszClassName = L"OGL3DWindow";			     //���w�������O�W��
	wc.lpfnWndProc = DefWindowProc;                  //���w�����B�z��� DefWindowProc�t�d�����̤p�ơB�̤j�ơB�����FlpfnWndProc�B�z�o�e�쵡�f�������A�p�����J�B�ƹ��ƥ�Bø�s�ШD


	assert(RegisterClassEx(&wc));                    //���U�������O wc�w�g�w�q�M��l�ƪ�WNDCLASSEX�ܼơA�]�t�������O���ݩʡA�Ҧp(lpfnWndProc)�B(lpszClassName)�B(hIcon)

	RECT rc = { 0,0,1024,768 };                      //{top,left,right,bottom}    width = right - left, height = bottom - top, so right = 1024, bottom = 768�C�_�l�I���k�B�W�A�פ��I�����B�U
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);         //�վ�����j�p�A�����˦��]�t���D��M���(WS_OVERLAPPED) | ���������D��(WS_CAPTION) | �����]�t�̤j�ơB�̤p�ơB�������s(WS_SYSMENU)

	//(dwExStyle)���ϥΥ����X�i�˦�, (lpClassName)�ϥ� Unicode �r�Ŧ�Хܵ������O���W��, (lpWindowName)�ϥ� Unicode �r�Ŧ�Хܵ������D, 
	//(dwStyle)�������˦��]����ةM���D��|�������D��|�����]�t�̤j�ơB�̤p�ơB�������s�B��������m�M�j�p
	//(x,y)���t�Φ۰ʿ�ܵ�����l��m,(nWidth,nHeight)�]�w�������e�M��, (hParent)�S�����h����, (hMenu)�S�����, (hInstance)�S�����, (lpParam)�S���S�O���ƾڭn�ǻ�
	m_handle = CreateWindowEx(NULL, L"OGL3DWindow", L"PardCode | OpenGL 3D Gmae", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL);


	assert(m_handle);                                //�p�Gm_handle���šA�h��ܿ��~�T���ä������
	ShowWindow((HWND)m_handle, SW_SHOW);             //��ܵ���
	UpdateWindow((HWND)m_handle);                    //��s����
}

OWindow::~OWindow()
{
		DestroyWindow((HWND)m_handle);               //�P������
}
