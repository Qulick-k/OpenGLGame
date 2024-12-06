#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <Windows.h>

OGame::OGame()
{
	m_display = std::unique_ptr<OWindow>(new OWindow());
}

OGame::~OGame()
{
}

void OGame::run()
{
	MSG msg;
	while (m_isRunning && !m_display->isClosed())
	{
		//檢查應用程式的訊息佇列中是否有訊息(PeekMessage), (&msg)使用地址將訊息儲存儲到變數中, (hWnd)檢查與目前執行緒關聯的視窗的訊息, 
		//(wMsgFilterMin),(wMsgFilterMax)設置要檢查訊息類型範圍設為NULL表示檢查所有類型的訊息, (PM_REMOVE)檢索訊息後移除
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))  
		{
			TranslateMessage(&msg);     //將原始鍵盤訊息轉換為字串訊息
			DispatchMessage(&msg);	    //將訊息發送到合適的視窗
		}

		Sleep(1);                       //讓CPU休息一下
	}
}

void OGame::quit()
{
	m_isRunning = false;
}
