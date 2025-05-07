#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>
#include <OGL3D/Window/OWindow.h>
#include <stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
	WNDCLASSEX wc = {};                              //�Ыئ۩w�q�������]�Ҧp���ε{�������ιϧάɭ��^
	wc.cbSize = sizeof(WNDCLASSEX);                  //��l�� WNDCLASSEX ���c�骺 cbSize �����A�ë��w���c�骺�j�p
	wc.lpszClassName = L"OGL3DDummyWindow";	         //���w�������O�W��
	wc.lpfnWndProc = DefWindowProcA;                  //&WndProc//DefWindowProc//���w�����B�z��� DefWindowProc�t�d�����̤p�ơB�̤j�ơB�����FlpfnWndProc�B�z�o�e�쵡�f�������A�p�����J�B�ƹ��ƥ�Bø�s�ШD
	wc.style = CS_OWNDC;                             //�ϥ�CS_OWNDC�i�H����OpenGL��DirectX����V�Ĳv

	auto classid = RegisterClassEx(&wc);                    //���U�������O wc�w�g�w�q�M��l�ƪ�WNDCLASSEX�ܼơA�]�t�������O���ݩʡA�Ҧp(lpfnWndProc)�B(lpszClassName)�B(hIcon)
	assert(classid);                                        //�p�Gclassid���šA�h��ܿ��~�T���ä������

	//RECT rc = { 0,0,1024,768 };                      //{top,left,right,bottom}    width = right - left, height = bottom - top, so right = 1024, bottom = 768�C�_�l�I���k�B�W�A�פ��I�����B�U
	//AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);         //�վ�����j�p�A�����˦��]�t���D��M���(WS_OVERLAPPED) | ���������D��(WS_CAPTION) | �����]�t�̤j�ơB�̤p�ơB�������s(WS_SYSMENU)

	//(dwExStyle)���ϥΥ����X�i�˦�, MAKEINTATOM(classid)���N(lpClassName)�ϥ� Unicode �r�Ŧ�Хܵ������O���W��, (lpWindowName)�ϥ� Unicode �r�Ŧ�Хܵ������D, 
	//(dwStyle)�������˦��]����ةM���D��|�������D��|�����]�t�̤j�ơB�̤p�ơB�������s�B��������m�M�j�p
	//(x,y)���t�Φ۰ʿ�ܵ�����l��m,(nWidth,nHeight)�]�w�������e�M��, (hParent)�S�����h����, (hMenu)�S�����, (hInstance)�S�����, (lpParam)�S���S�O���ƾڭn�ǻ�
	/*auto dummyWindow = CreateWindowEx(NULL, MAKEINTATOM(classid), L"", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);*/
	HWND dummyWindow = CreateWindowEx(
		0,
		MAKEINTATOM(classid),
		L"OGL3DDummyWindow",
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		wc.hInstance,
		0);

	assert(dummyWindow);                                //�p�GdummyWindow���šA�h��ܿ��~�T���ä������

	auto dummyDC = GetDC(dummyWindow);                                                  //���odummyWindow��DC

	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};                                          //�Ы�PIXELFORMATDESCRIPTOR���c��,�ê�l�ƩҦ��������w�]��
	pixelFormatDesc.nSize = sizeof(pixelFormatDesc);                               //�]�mPIXELFORMATDESCRIPTOR���c�骺�j�p
	pixelFormatDesc.nVersion = 1;                                                        //�]�m���c����������1
	pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;                                          //�]�m�����榡����,�]�ARGBA�C��ҫ�
	pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;     //�]�m�����榡����,�]�ARGBA�C��ҫ��B�䴩OpenGL�B�ϥ����w��(�קK�e���{�{)
	pixelFormatDesc.cColorBits = 32;                                                     //�]�m�C���Ƭ�32��,���B��B�ũM�z���U 8 ��
	pixelFormatDesc.cAlphaBits = 8;                                                      //�]�mAlpha�q�D��8��
	pixelFormatDesc.cDepthBits = 24;                                                     //�]�m�`�׽w�İϬ�24��,�Ω�3D��V���`�״���
	pixelFormatDesc.cStencilBits = 8;                                                    //�]�m�ҪO�w�İϬ�8��,�Ω�ҪO����
	pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;                                         //�]�m�Dø�ϼh,�]�O�̱`�Ϊ��h����


	int pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDesc);                     //(ChoosePixelFormat)��̱ܳ��񪺹����榡
	SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDesc);							     //(SetPixelFormat)���]�ƤW�U��]�m�����榡

	HGLRC dummyContext = wglCreateContext(dummyDC);                                       //�Ы�OpenGL��V�W�U��
	assert(dummyContext);                                                                //�p�GdummyContext����,�h��ܿ��~�T���ä������

	bool res = wglMakeCurrent(dummyDC, dummyContext);                                               //�ҥ�OpenGL��V�W�U��,�N��]�m����e���ʤW�U��
	assert(res);

	if (!gladLoadWGL(dummyDC)) 													         //�[��WGL,(gladLoadWGL)WGL�OWindows���x�W�POpenGL�������X�i,���t�d���f�޲z�M�W�U��Ы�
		OGL3D_ERROR("OGraphicsEngine - gladLoadWGL failed");

	if (!gladLoadGL()) 													                 //�[��OpenGL���,�T�O�i�H�ϥ�OpenGL��API�i���V
		OGL3D_ERROR("OGraphicsEngine - gladLoadGL failed");


	wglMakeCurrent(dummyDC, 0);                                                          //�Ѱ��W�U��j�w�G�T�O��e�W�U��L��
	wglDeleteContext(dummyContext);                                                      //�R����V�W�U��G����OpenGL��V�W�U��e�Ϊ��귽
	ReleaseDC(dummyWindow, dummyDC);                                                     //����]�ƤW�U��G����P����������ø�ϱ��f
	DestroyWindow(dummyWindow);                                                          //�P�������G�M�z�����e�Ϊ��t�θ귽�C
}

OGraphicsEngine::~OGraphicsEngine()
{
}


