#include <OGL3D/Window/OWindow.h>  //注意斜線方向，不然開不了檔案
#include <Windows.h>               //使用Win32 API
#include <assert.h> 			   //使用assert函數，只用於開發測試，當 assert 中的條件為假時，程式會顯示錯誤訊息並中止執行

OWindow::OWindow()
{ 
	WNDCLASSEX wc = {};                              //創建自定義的視窗（例如應用程式視窗或圖形界面）
	wc.cbSize = sizeof(WNDCLASSEX);                  //初始化 WNDCLASSEX 結構體的 cbSize 成員，並指定結構體的大小
	wc.lpszClassName = L"OGL3DWindow";			     //指定視窗類別名稱
	wc.lpfnWndProc = DefWindowProc;                  //指定視窗處理函數 DefWindowProc負責視窗最小化、最大化、關閉；lpfnWndProc處理發送到窗口的消息，如按鍵輸入、滑鼠事件、繪製請求

	RegisterClassEx(&wc);                            //註冊視窗類別 wc已經定義和初始化的WNDCLASSEX變數，包含視窗類別的屬性，例如(lpfnWndProc)、(lpszClassName)、(hIcon)
}

OWindow::~OWindow()
{
}
