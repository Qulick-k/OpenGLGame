#include <OGL3D/Window/OWindow.h>  //�`�N�׽u��V�A���M�}���F�ɮ�
#include <OGL3D/Game/OGame.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <Windows.h>               //�ϥ�Win32 API
#include <assert.h> 			   //�ϥ�assert���,�u�Ω�}�o����,�� assert �������󬰰���,�{���|��ܿ��~�T���ä������

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)   //(LRESULT)��ܮ����B�z�����G, (CALLBACK)�w�q�եά��w, (WndProc)��������ƦW��, (HWND)�����Х�, (UINT)�T���Х�, (WPARAM)�ǻ���L���䪺�N�X�ηƹ����䪺���A, (LPARAM )�ǻ����Ъ�����
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		OWindow* window = (OWindow *)GetWindowLongPtr(hwnd, GWLP_USERDATA);   //(OWindow*) �O�j�������ഫ, (GetWindowLongPtr)��^�@��LONG_PTR�������ȥΨӦs�x���w, (hwnd)���ѭn�q���˯��ƾڪ�����, (GWLP_USERDATA)�Τ�۩w�q���ƾ�
		//window->onDestroy();												  //�ե�window���w�ҫ��V��H���W��onDestroy()�����
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);                                //�o�e�@�Ӱh�X����,�q���t�����ε{�ǧY�N�h�X,�����ε{���������`���פ�
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);   //�p�G�S���B�z������,�h�եιw�]�������B�z���
	}
	return NULL;
}


OWindow::OWindow()
{ 
	WNDCLASSEX wc = {};                              //�Ыئ۩w�q�������]�Ҧp���ε{�������ιϧάɭ��^ WNDCLASSEX �O Windows Class Extended ���Y�g, ��ܡu�X�i�����������c�v
	wc.cbSize = sizeof(WNDCLASSEX);                  //��l�� WNDCLASSEX ���c�骺 cbSize �����A�ë��w���c�骺�j�p
	wc.lpszClassName = L"OGL3DWindow";			     //���w�������O�W��
	wc.lpfnWndProc = &WndProc;                       //DefWindowProc//���w�����B�z��� DefWindowProc�t�d�����̤p�ơB�̤j�ơB�����FlpfnWndProc�B�z�o�e������������A�p�����J�B�ƹ��ƥ�Bø�s�ШD
	wc.style = CS_OWNDC;		                     //���w�������O���˦�,CS_OWNDC��ܵ����֦��ۤv���]�ƤW�U��, Class Style Own Device Context ���Y�g�A��ܡu�������֦��ۤv���]�ƤW�U��]Device Context, DC�^�v

	auto classid = RegisterClassEx(&wc);                    //���U�������O wc�w�g�w�q�M��l�ƪ�WNDCLASSEX�ܼơA�]�t�������O���ݩʡA�Ҧp(lpfnWndProc)�B(lpszClassName)�B(hIcon)
	assert(classid);                                        //�p�Gclassid���šA�h��ܿ��~�T���ä������

	RECT rc = { 0,0,1024,768 };                      //{top,left,right,bottom}    width = right - left, height = bottom - top, so right = 1024, bottom = 768�C�_�l�I���k�B�W�A�פ��I�����B�U
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);         //�վ�����j�p�A�����˦��]�t���D��M���(WS_OVERLAPPED) | ���������D��(WS_CAPTION) | �����]�t�̤j�ơB�̤p�ơB�������s(WS_SYSMENU)

	//(dwExStyle)���ϥΥ����X�i�˦�, MAKEINTATOM(classid)���N(lpClassName)�ϥ� Unicode �r�Ŧ�Хܵ������O���W��, (lpWindowName)�ϥ� Unicode �r�Ŧ�Хܵ������D, 
	//(dwStyle)�������˦��]����ةM���D��|�������D��|�����]�t�̤j�ơB�̤p�ơB�������s�B��������m�M�j�p
	//(x,y)���t�Φ۰ʿ�ܵ�����l��m,(nWidth,nHeight)�]�w�������e�M��, (hParent)�S�����h����, (hMenu)�S�����, (hInstance)�S�����, (lpParam)�S���S�O���ƾڭn�ǻ�
	m_handle = CreateWindowEx(NULL, MAKEINTATOM(classid), L"PardCode | OpenGL 3D Gmae", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL);


	assert(m_handle);                                //�p�Gm_handle���šA�h��ܿ��~�T���ä������

	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);  //(SetWindowLongPtr)�]�m���w���������㫬�ƾکΫ��w, ((HWND)m_handle)���ѭn�]�m���S�w����, (GWLP_USERDATA)���ܷQ�n�]�m���ƾ������A(LONG_PTR)this)���w�n�]�m����

	ShowWindow((HWND)m_handle, SW_SHOW);             //��ܵ���
	UpdateWindow((HWND)m_handle);                    //��s����



	//Creating OpenGL Render Context

	auto hDC = GetDC(HWND(m_handle));                          //���o�������]�ƤW�U��]Device Context, DC�^,�j���૬HWND(m_handle),�Nm_handle,���]�O��������N�X�^�ǻ���GetDC�C

	int pixelFormatAttributes[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,                       //�䴩�N��V��X�����
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,					   //�䴩OpenGL��V
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,						   //�䴩���w�İ�
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,	   //�䴩�w��[�t
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,				   //���������]�m��RGBA
		WGL_COLOR_BITS_ARB, 32,								   //�C��w�İϪ��줸�`�׬�32���
		WGL_DEPTH_BITS_ARB, 24,								   //�`�׽w�İϪ��줸�`�׬�24���
		WGL_STENCIL_BITS_ARB, 8,							   //�ҪO�w�İϪ��줸�`�׬�8���
		0													   //�����аO,����ݩʰ}�C������
	};

	int pixelFormat = 0; 									   //�x�s��w�������榡���ޡ]��ƭȡ^
	UINT numFormats = 0;									   //�x�s�ǰt���󪺹����榡�ƶq

	/*
	(wglChoosePixelFormatARB) �OOpenGL���X�i��ơA�Ω�q�����榡�ݩʦC����ܲŦX���󪺹����榡�C
	(hDC) �]�ƤW�U��]Device Context�^������N�X�A�Ω���w�P�����榡���p������
	(pixelFormatAttributes) �ݩʰ}�C�A�Ω���w��ܱ���
	(nullptr) �@��]��nullptr,��ܵL�����w�B�~���B�I�ݩ�
	(1) �ШD���@�ӹ����榡
	(&pixelFormat) �x�s��w�������榡���ޡ]��ƭȡ^
	(&numFormats) �x�s�ǰt���󪺹����榡�ƶq
	��ܲŦX���w�ݩʪ������榡�A�ì� OpenGL ��V���n�ǳơC�p�G��ܦ��\�ApixelFormat ���N�]�t�ҿ諸�����榡���ޡA�ѫ���]�m�ϥΡC
	*/
	wglChoosePixelFormatARB(hDC, pixelFormatAttributes, nullptr, 1, &pixelFormat, &numFormats);   
	assert(numFormats);

	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};               //�@�ӵ��c,�ΨӴy�z�]�ƤW�U��]device context�^�Ҥ䴩�������榡,pixelFormatDesc�Ψӱ��������榡��������T�C
	DescribePixelFormat(                                      // �z�LDescribePixelFormat��ơA��RPIXELFORMATDESCRIPTOR���c�A�H�˯��S�w�����榡���Բ��ݩ�
		hDC,                                                  //�]�ƤW�U�媺����N�X                                      
		pixelFormat, 										  //�����榡������
		sizeof(PIXELFORMATDESCRIPTOR), 					      //���c���j�p(�H�줸�լ����)
		&pixelFormatDesc									  //���������榡��T������
	);
	SetPixelFormat(											  // �ϥ�SetPixelFormat��ơA���]�ƤW�U��]device context�AhDC�^�]�m�S�w�������榡�C
		hDC, 												  //�]�ƤW�U�媺����N�X
		pixelFormat, 										  //�����榡������
		&pixelFormatDesc									  //�����榡�y�z����
	);


	int openGLAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,                                     // OpenGL ���D�������� 4, �N���۴�V�W�U��N��� OpenGL 4.x ���\��
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,                                     // OpenGL ������������ 6, �N���۴�V�W�U��N��� OpenGL 4.6 ���\��
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,       // �w�q OpenGL ���t�m���]Profile�^, ���w�ϥ� Core Profile (�֤߰t�m),���]�t�Q OpenGL �аO���L�ɪ��\��
		0
	};

	m_context = wglCreateContextAttribsARB(									  // �Ы� OpenGL ��V�W�U�� (Rendering Context)�A�ë��w���ݩʡC
		hDC, 																  // ���V������ø������,�O�Ы� OpenGL ��V�W�U�媺��¦
		0,																      // �]�� 0,��ܸӴ�V�W�U�夣�@�ɨ�L�W�U�媺���A
		openGLAttributes													  // �]�t��V�W�U�媺�ݩʦC��]�Ҧp�������B�t�m���^,�e�����{���X��,�w�q�F openGLAttributes,�Ω�]�m OpenGL 4.6 ���W�U��H�ή֤߰t�m�C
	);
	assert(m_context);
}

OWindow::~OWindow()
{
	wglDeleteContext(HGLRC(m_context));          //HGLRC(Handle to GL Rendering Context),m_context�����ഫ��HGLRC�榡,�ǻ�����ƶi��R��. �R�� OpenGL ��V�W�U�� (Rendering Context),�H����귽�òM�zø������
	DestroyWindow((HWND)m_handle);               //�P������
}

ORect OWindow::getInnerSize()
{
	RECT rc = {};                                          //RECT ���c�Ω�w�q�x�ΰϰ쪺���W���M�k�U���y��
	GetClientRect((HWND)m_handle, &rc);                    //���oViewport���Ȥ�ϰ�j�p, GetClientRect ��ƥΩ���oViewport�Ȥ�ϰ쪺�j�p,�Y���]�A���D��M��ت��ϰ�
	return ORect(rc.right - rc.left, rc.bottom - rc.top);  //��^Viewport�������j�p,�Y�Ȥ�ϰ쪺�e�M��
}

void OWindow::makeCurrentContext()
{
	wglMakeCurrent(GetDC(HWND(m_handle)), HGLRC(m_context));               //�N���w����V�W�U��]Rendering Context, RC�^�j�w��]�ƤW�U��]Device Context, DC�^,�� OpenGL ø�ϩR�O�v�T�ӳ]�ƤW�U��Ҵy�z�����f
}

void OWindow::present(bool vsync)
{
	wglSwapIntervalEXT(vsync);                                             //�]�w�洫�w�İϮɬO�_�ҥΫ����P�B (Vertical Synchronization, V-Sync)
	wglSwapLayerBuffers(GetDC(HWND(m_handle)), WGL_SWAP_MAIN_PLANE);       //���� OpenGL �����w�İϥ洫,��x�w�İϪ����e�e�{�b�ù��W,�ت��O���Ѭy�Z���ϧ���ܮĪG. wglSwapLayerBuffers �Ω����h�w�İϥ洫 (Layer Buffer Swapping), WGL_SWAP_MAIN_PLANE ���w���ӥ洫�D�h���w�İϤ��e��e�x,������ܦb�ù��W
}

/*void OWindow::onDestroy()
{
	m_handle = nullptr;                              //�Nm_handle�]�m����
}

bool OWindow::isClosed()
{
	return !m_handle;
}*/
