#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <Windows.h>

OGame::OGame()
{
	m_display = std::make_unique<OWindow>();        //使用智慧指針std::unique_ptr管理一個動態分配的OWindow對象，將其分配給成員變數m_display //使用make_unique<OWindow>()取代unique_ptr<OWindow>(new OWindow())
}

OGame::~OGame()
{
}

void OGame::run()
{
	
	while (m_isRunning) //利用PostQuitMessage(0)取代&& !m_display->isClosed()
	{
		MSG msg = {};        //定義一個MSG結構體變數

		//檢查應用程式的訊息佇列中是否有訊息(PeekMessage), (&msg)使用地址將訊息儲存儲到變數中, (hWnd)檢查與目前執行緒關聯的視窗的訊息, 
		//(wMsgFilterMin),(wMsgFilterMax)設置要檢查訊息類型範圍設為NULL表示檢查所有類型的訊息, (PM_REMOVE)檢索訊息後移除
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))  
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

		Sleep(1);                       //讓CPU休息一下
	}
}

void OGame::quit()
{
	m_isRunning = false;
}
