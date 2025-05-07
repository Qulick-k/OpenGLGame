#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <assert.h>
#include <OGL3D/Window/OWindow.h>
#include <stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
	WNDCLASSEX wc = {};                              //創建自定義的視窗（例如應用程式視窗或圖形界面）
	wc.cbSize = sizeof(WNDCLASSEX);                  //初始化 WNDCLASSEX 結構體的 cbSize 成員，並指定結構體的大小
	wc.lpszClassName = L"OGL3DDummyWindow";	         //指定視窗類別名稱
	wc.lpfnWndProc = DefWindowProcA;                  //&WndProc//DefWindowProc//指定視窗處理函數 DefWindowProc負責視窗最小化、最大化、關閉；lpfnWndProc處理發送到窗口的消息，如按鍵輸入、滑鼠事件、繪製請求
	wc.style = CS_OWNDC;                             //使用CS_OWNDC可以提高OpenGL或DirectX的渲染效率

	auto classid = RegisterClassEx(&wc);                    //註冊視窗類別 wc已經定義和初始化的WNDCLASSEX變數，包含視窗類別的屬性，例如(lpfnWndProc)、(lpszClassName)、(hIcon)
	assert(classid);                                        //如果classid為空，則顯示錯誤訊息並中止執行

	//RECT rc = { 0,0,1024,768 };                      //{top,left,right,bottom}    width = right - left, height = bottom - top, so right = 1024, bottom = 768。起始點為右、上，終止點為左、下
	//AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);         //調整視窗大小，視窗樣式包含標題欄和邊框(WS_OVERLAPPED) | 視窗有標題欄(WS_CAPTION) | 視窗包含最大化、最小化、關閉按鈕(WS_SYSMENU)

	//(dwExStyle)不使用任何擴展樣式, MAKEINTATOM(classid)取代(lpClassName)使用 Unicode 字符串標示視窗類別的名稱, (lpWindowName)使用 Unicode 字符串標示視窗標題, 
	//(dwStyle)視窗的樣式包刮邊框和標題欄|視窗標題欄|視窗包含最大化、最小化、關閉按鈕、視窗的位置和大小
	//(x,y)讓系統自動選擇視窗初始位置,(nWidth,nHeight)設定視窗的寬和高, (hParent)沒有父層視窗, (hMenu)沒有菜單, (hInstance)沒有實例, (lpParam)沒有特別的數據要傳遞
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

	assert(dummyWindow);                                //如果dummyWindow為空，則顯示錯誤訊息並中止執行

	auto dummyDC = GetDC(dummyWindow);                                                  //取得dummyWindow的DC

	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};                                          //創建PIXELFORMATDESCRIPTOR結構體,並初始化所有成員為預設值
	pixelFormatDesc.nSize = sizeof(pixelFormatDesc);                               //設置PIXELFORMATDESCRIPTOR結構體的大小
	pixelFormatDesc.nVersion = 1;                                                        //設置結構的版本號為1
	pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;                                          //設置像素格式類型,包括RGBA顏色模型
	pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;     //設置像素格式類型,包括RGBA顏色模型、支援OpenGL、使用雙緩衝(避免畫面閃爍)
	pixelFormatDesc.cColorBits = 32;                                                     //設置顏色位數為32位,紅、綠、藍和透明各 8 位
	pixelFormatDesc.cAlphaBits = 8;                                                      //設置Alpha通道為8位
	pixelFormatDesc.cDepthBits = 24;                                                     //設置深度緩衝區為24位,用於3D渲染的深度測試
	pixelFormatDesc.cStencilBits = 8;                                                    //設置模板緩衝區為8位,用於模板測試
	pixelFormatDesc.iLayerType = PFD_MAIN_PLANE;                                         //設置主繪圖層,也是最常用的層類型


	int pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDesc);                     //(ChoosePixelFormat)選擇最接近的像素格式
	SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDesc);							     //(SetPixelFormat)為設備上下文設置像素格式

	HGLRC dummyContext = wglCreateContext(dummyDC);                                       //創建OpenGL渲染上下文
	assert(dummyContext);                                                                //如果dummyContext為空,則顯示錯誤訊息並中止執行

	bool res = wglMakeCurrent(dummyDC, dummyContext);                                               //啟用OpenGL渲染上下文,將其設置為當前活動上下文
	assert(res);

	if (!gladLoadWGL(dummyDC)) 													         //加載WGL,(gladLoadWGL)WGL是Windows平台上與OpenGL相關的擴展,它負責窗口管理和上下文創建
		OGL3D_ERROR("OGraphicsEngine - gladLoadWGL failed");

	if (!gladLoadGL()) 													                 //加載OpenGL函數,確保可以使用OpenGL的API進行渲染
		OGL3D_ERROR("OGraphicsEngine - gladLoadGL failed");


	wglMakeCurrent(dummyDC, 0);                                                          //解除上下文綁定：確保當前上下文無效
	wglDeleteContext(dummyContext);                                                      //刪除渲染上下文：釋放OpenGL渲染上下文占用的資源
	ReleaseDC(dummyWindow, dummyDC);                                                     //釋放設備上下文：釋放與視窗相關的繪圖接口
	DestroyWindow(dummyWindow);                                                          //銷毀視窗：清理視窗占用的系統資源。
}

OGraphicsEngine::~OGraphicsEngine()
{
}


