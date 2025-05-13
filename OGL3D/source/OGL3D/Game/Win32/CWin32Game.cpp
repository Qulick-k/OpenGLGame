#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <Windows.h>
//#include <OGL3D/Graphics/OGraphicsEngine.h> 
/*  #include 指令
#include 指令
作用：
將指定的標頭檔案內容插入到當前檔案中，以便使用標頭檔案中定義的類、函數或其他程式碼。
語法：
#include <標頭檔案>：表示從標準或全局路徑中搜尋檔案。
#include "標頭檔案"：表示從當前檔案所在目錄或指定的路徑中搜尋檔案。
*/


void OGame::run()
{
	onCreate();              //執行onCreate()函數
	while (m_isRunning)      //利用PostQuitMessage(0)取代&& !m_display->isClosed()
	{
		MSG msg = {};        //定義一個MSG結構體變數

		//檢查應用程式的訊息佇列中是否有訊息(PeekMessage), (&msg)使用地址將訊息儲存儲到變數中, (hWnd)檢查與目前執行緒關聯的視窗的訊息, 
		//(wMsgFilterMin),(wMsgFilterMax)設置要檢查訊息類型範圍設為NULL表示檢查所有類型的訊息, (PM_REMOVE)檢索訊息後移除
		if (PeekMessage(&msg, HWND(), NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)     //WM_QUIT是由應用程式主動生成的消息，通常透過調用PostQuitMessage()發送
			{
				m_isRunning = false;
				continue;
			}
			else
			{
				TranslateMessage(&msg);     //將原始鍵盤訊息轉換為字串訊息
				DispatchMessage(&msg);	    //將訊息發送到合適的視窗
			}
		}

		onUpdateInternal();            //onUpdateInternal取代Sleep(1);                       //讓CPU休息一下
	}

	onQuit();                  //執行onQuit()函數
}