#include <OGL3D/Window/OWindow.h>  //注意斜線方向，不然開不了檔案
#include <Windows.h>               //使用Win32 API
#include <assert.h> 			   //使用assert函數，只用於開發測試，當 assert 中的條件為假時，程式會顯示錯誤訊息並中止執行

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)   //(LRESULT)表示消息處理的結果, (CALLBACK)定義調用約定, (WndProc)視窗的函數名稱, (HWND)視窗標示, (UINT)訊息標示, (WPARAM)傳遞鍵盤按鍵的代碼或滑鼠按鍵的狀態, (LPARAM )傳遞鼠標的坐標
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		OWindow* window = (OWindow *)GetWindowLongPtr(hwnd, GWLP_USERDATA);   //(OWindow*) 是強制類型轉換, (GetWindowLongPtr)返回一個LONG_PTR類型的值用來存儲指針, (hwnd)標識要從中檢索數據的視窗, (GWLP_USERDATA)用戶自定義的數據
		window->onDestroy();												  //調用window指針所指向對象中名為onDestroy()的函數
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);   //如果沒有處理的消息，則調用預設的視窗處理函數
	}
	return NULL;
}









OWindow::OWindow()
{ 
	WNDCLASSEX wc = {};                              //創建自定義的視窗（例如應用程式視窗或圖形界面）
	wc.cbSize = sizeof(WNDCLASSEX);                  //初始化 WNDCLASSEX 結構體的 cbSize 成員，並指定結構體的大小
	wc.lpszClassName = L"OGL3DWindow";			     //指定視窗類別名稱
	wc.lpfnWndProc = &WndProc;        //DefWindowProc//指定視窗處理函數 DefWindowProc負責視窗最小化、最大化、關閉；lpfnWndProc處理發送到窗口的消息，如按鍵輸入、滑鼠事件、繪製請求


	assert(RegisterClassEx(&wc));                    //註冊視窗類別 wc已經定義和初始化的WNDCLASSEX變數，包含視窗類別的屬性，例如(lpfnWndProc)、(lpszClassName)、(hIcon)

	RECT rc = { 0,0,1024,768 };                      //{top,left,right,bottom}    width = right - left, height = bottom - top, so right = 1024, bottom = 768。起始點為右、上，終止點為左、下
	AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);         //調整視窗大小，視窗樣式包含標題欄和邊框(WS_OVERLAPPED) | 視窗有標題欄(WS_CAPTION) | 視窗包含最大化、最小化、關閉按鈕(WS_SYSMENU)

	//(dwExStyle)不使用任何擴展樣式, (lpClassName)使用 Unicode 字符串標示視窗類別的名稱, (lpWindowName)使用 Unicode 字符串標示視窗標題, 
	//(dwStyle)視窗的樣式包刮邊框和標題欄|視窗標題欄|視窗包含最大化、最小化、關閉按鈕、視窗的位置和大小
	//(x,y)讓系統自動選擇視窗初始位置,(nWidth,nHeight)設定視窗的寬和高, (hParent)沒有父層視窗, (hMenu)沒有菜單, (hInstance)沒有實例, (lpParam)沒有特別的數據要傳遞
	m_handle = CreateWindowEx(NULL, L"OGL3DWindow", L"PardCode | OpenGL 3D Gmae", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, NULL, NULL);


	assert(m_handle);                                //如果m_handle為空，則顯示錯誤訊息並中止執行

	SetWindowLongPtr((HWND)m_handle, GWLP_USERDATA, (LONG_PTR)this);  //(SetWindowLongPtr)設置指定視窗的長整型數據或指針, ((HWND)m_handle)標識要設置的特定視窗, (GWLP_USERDATA)指示想要設置的數據類型，(LONG_PTR)this)指定要設置的值

	ShowWindow((HWND)m_handle, SW_SHOW);             //顯示視窗
	UpdateWindow((HWND)m_handle);                    //更新視窗
}

OWindow::~OWindow()
{
		DestroyWindow((HWND)m_handle);               //銷毀視窗
}

void OWindow::onDestroy()
{
	m_handle = nullptr;                              //將m_handle設置為空
}

bool OWindow::isClosed()
{
	return !m_handle;
}
