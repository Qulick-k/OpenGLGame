#include <OGL3D/Window/OWindow.h>  //注意斜線方向，不然開不了檔案
#include <OGL3D/Game/OGame.h>
#include <glad/glad_wgl.h>
#include <glad/glad.h>
#include <Windows.h>               //使用Win32 API
#include <assert.h> 			   //使用assert函數,只用於開發測試,當 assert 中的條件為假時,程式會顯示錯誤訊息並中止執行

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)   //(LRESULT)表示消息處理的結果, (CALLBACK)定義調用約定, (WndProc)視窗的函數名稱, (HWND)視窗標示, (UINT)訊息標示, (WPARAM)傳遞鍵盤按鍵的代碼或滑鼠按鍵的狀態, (LPARAM )傳遞鼠標的坐標
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		OWindow* window = (OWindow *)GetWindowLongPtr(hwnd, GWLP_USERDATA);   //(OWindow*) 是強制類型轉換, (GetWindowLongPtr)返回一個LONG_PTR類型的值用來存儲指針, (hwnd)標識要從中檢索數據的視窗, (GWLP_USERDATA)用戶自定義的數據
		//window->onDestroy();												  //調用window指針所指向對象中名為onDestroy()的函數
		break;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);                                //發送一個退出消息,通知系統應用程序即將退出,使應用程式的消息循環終止
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);   //如果沒有處理的消息,則調用預設的視窗處理函數
	}
	return NULL;
}


OWindow::OWindow()
{ 
	WNDCLASSEX wc = {};                              //創建自定義的視窗（例如應用程式視窗或圖形界面） WNDCLASSEX 是 Windows Class Extended 的縮寫, 表示「擴展的視窗類結構」
	wc.cbSize = sizeof(WNDCLASSEX);                  //初始化 WNDCLASSEX 結構體的 cbSize 成員，並指定結構體的大小
	wc.lpszClassName = L"OGL3DWindow";			     //指定視窗類別名稱
	wc.lpfnWndProc = &WndProc;                       //DefWindowProc//指定視窗處理函數 DefWindowProc負責視窗最小化、最大化、關閉；lpfnWndProc處理發送到視窗的消息，如按鍵輸入、滑鼠事件、繪製請求
	wc.style = CS_OWNDC;		                     //指定視窗類別的樣式,CS_OWNDC表示視窗擁有自己的設備上下文, Class Style Own Device Context 的縮寫，表示「視窗類擁有自己的設備上下文（Device Context, DC）」

	auto classid = RegisterClassEx(&wc);                    //註冊視窗類別 wc已經定義和初始化的WNDCLASSEX變數，包含視窗類別的屬性，例如(lpfnWndProc)、(lpszClassName)、(hIcon)
	assert(classid);                                        //如果classid為空，則顯示錯誤訊息並中止執行

	RECT rc = { 0,0,1024,768 };                      //{top,left,right,bottom}    width = right - left, height = bottom - top, so right = 1024, bottom = 768。起始點為右、上，終止點為左、下
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);         //調整視窗大小，視窗樣式包含標題欄和邊框(WS_OVERLAPPED) | 視窗有標題欄(WS_CAPTION) | 視窗包含最大化、最小化、關閉按鈕(WS_SYSMENU)

	//(dwExStyle)不使用任何擴展樣式, MAKEINTATOM(classid)取代(lpClassName)使用 Unicode 字符串標示視窗類別的名稱, (lpWindowName)使用 Unicode 字符串標示視窗標題, 
	//(dwStyle)視窗的樣式包刮邊框和標題欄|視窗標題欄|視窗包含最大化、最小化、關閉按鈕、視窗的位置和大小
	//(x,y)讓系統自動選擇視窗初始位置,(nWidth,nHeight)設定視窗的寬和高, (hParent)沒有父層視窗, (hMenu)沒有菜單, (hInstance)沒有實例, (lpParam)沒有特別的數據要傳遞
	m_handle = CreateWindowEx(NULL, MAKEINTATOM(classid), L"PardCode | OpenGL 3D Gmae", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL);


	assert(m_handle);                                //如果m_handle為空，則顯示錯誤訊息並中止執行

	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);  //(SetWindowLongPtr)設置指定視窗的長整型數據或指針, ((HWND)m_handle)標識要設置的特定視窗, (GWLP_USERDATA)指示想要設置的數據類型，(LONG_PTR)this)指定要設置的值

	ShowWindow((HWND)m_handle, SW_SHOW);             //顯示視窗
	UpdateWindow((HWND)m_handle);                    //更新視窗



	//Creating OpenGL Render Context

	auto hDC = GetDC(HWND(m_handle));                          //取得視窗的設備上下文（Device Context, DC）,強制轉型HWND(m_handle),將m_handle,假設是視窗控制代碼）傳遞給GetDC。

	int pixelFormatAttributes[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,                       //支援將渲染輸出到視窗
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,					   //支援OpenGL渲染
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,						   //支援雙緩衝區
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,	   //支援硬體加速
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,				   //像素類型設置為RGBA
		WGL_COLOR_BITS_ARB, 32,								   //顏色緩衝區的位元深度為32位數
		WGL_DEPTH_BITS_ARB, 24,								   //深度緩衝區的位元深度為24位數
		WGL_STENCIL_BITS_ARB, 8,							   //模板緩衝區的位元深度為8位數
		0													   //結束標記,表示屬性陣列的結束
	};

	int pixelFormat = 0; 									   //儲存選定的像素格式索引（整數值）
	UINT numFormats = 0;									   //儲存匹配條件的像素格式數量

	/*
	(wglChoosePixelFormatARB) 是OpenGL的擴展函數，用於從像素格式屬性列表中選擇符合條件的像素格式。
	(hDC) 設備上下文（Device Context）的控制代碼，用於指定與像素格式關聯的視窗
	(pixelFormatAttributes) 屬性陣列，用於指定選擇條件
	(nullptr) 一般設為nullptr,表示無須指定額外的浮點屬性
	(1) 請求找到一個像素格式
	(&pixelFormat) 儲存選定的像素格式索引（整數值）
	(&numFormats) 儲存匹配條件的像素格式數量
	選擇符合指定屬性的像素格式，並為 OpenGL 渲染做好準備。如果選擇成功，pixelFormat 中將包含所選的像素格式索引，供後續設置使用。
	*/
	wglChoosePixelFormatARB(hDC, pixelFormatAttributes, nullptr, 1, &pixelFormat, &numFormats);   
	assert(numFormats);

	PIXELFORMATDESCRIPTOR pixelFormatDesc = {};               //一個結構,用來描述設備上下文（device context）所支援的像素格式,pixelFormatDesc用來接收像素格式的相關資訊。
	DescribePixelFormat(                                      // 透過DescribePixelFormat函數，填充PIXELFORMATDESCRIPTOR結構，以檢索特定像素格式的詳細屬性
		hDC,                                                  //設備上下文的控制代碼                                      
		pixelFormat, 										  //像素格式的索引
		sizeof(PIXELFORMATDESCRIPTOR), 					      //結構的大小(以位元組為單位)
		&pixelFormatDesc									  //接收像素格式資訊的指標
	);
	SetPixelFormat(											  // 使用SetPixelFormat函數，為設備上下文（device context，hDC）設置特定的像素格式。
		hDC, 												  //設備上下文的控制代碼
		pixelFormat, 										  //像素格式的索引
		&pixelFormatDesc									  //像素格式描述指標
	);


	int openGLAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,                                     // OpenGL 的主版本號為 4, 意味著渲染上下文將支持 OpenGL 4.x 的功能
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,                                     // OpenGL 的次版本號為 6, 意味著渲染上下文將支持 OpenGL 4.6 的功能
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,       // 定義 OpenGL 的配置文件（Profile）, 指定使用 Core Profile (核心配置),不包含被 OpenGL 標記為過時的功能
		0
	};

	m_context = wglCreateContextAttribsARB(									  // 創建 OpenGL 渲染上下文 (Rendering Context)，並指定其屬性。
		hDC, 																  // 指向視窗的繪圖環境,是創建 OpenGL 渲染上下文的基礎
		0,																      // 設為 0,表示該渲染上下文不共享其他上下文的狀態
		openGLAttributes													  // 包含渲染上下文的屬性列表（例如版本號、配置文件）,前面的程式碼中,定義了 openGLAttributes,用於設置 OpenGL 4.6 的上下文以及核心配置。
	);
	assert(m_context);
}

OWindow::~OWindow()
{
	wglDeleteContext(HGLRC(m_context));          //HGLRC(Handle to GL Rendering Context),m_context指標轉換為HGLRC格式,傳遞給函數進行刪除. 刪除 OpenGL 渲染上下文 (Rendering Context),以釋放資源並清理繪圖環境
	DestroyWindow((HWND)m_handle);               //銷毀視窗
}

ORect OWindow::getInnerSize()
{
	RECT rc = {};                                          //RECT 結構用於定義矩形區域的左上角和右下角座標
	GetClientRect((HWND)m_handle, &rc);                    //取得Viewport的客戶區域大小, GetClientRect 函數用於取得Viewport客戶區域的大小,即不包括標題欄和邊框的區域
	return ORect(rc.right - rc.left, rc.bottom - rc.top);  //返回Viewport的內部大小,即客戶區域的寬和高
}

void OWindow::makeCurrentContext()
{
	wglMakeCurrent(GetDC(HWND(m_handle)), HGLRC(m_context));               //將指定的渲染上下文（Rendering Context, RC）綁定到設備上下文（Device Context, DC）,使 OpenGL 繪圖命令影響該設備上下文所描述的窗口
}

void OWindow::present(bool vsync)
{
	wglSwapIntervalEXT(vsync);                                             //設定交換緩衝區時是否啟用垂直同步 (Vertical Synchronization, V-Sync)
	wglSwapLayerBuffers(GetDC(HWND(m_handle)), WGL_SWAP_MAIN_PLANE);       //執行 OpenGL 的雙緩衝區交換,後台緩衝區的內容呈現在螢幕上,目的是提供流暢的圖形顯示效果. wglSwapLayerBuffers 用於執行層緩衝區交換 (Layer Buffer Swapping), WGL_SWAP_MAIN_PLANE 指定應該交換主層的緩衝區內容到前台,讓其顯示在螢幕上
}

/*void OWindow::onDestroy()
{
	m_handle = nullptr;                              //將m_handle設置為空
}

bool OWindow::isClosed()
{
	return !m_handle;
}*/
