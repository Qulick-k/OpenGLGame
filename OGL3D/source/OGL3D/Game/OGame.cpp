#include <OGL3D/Game/OGame.h>
#include <OGL3D/Window/OWindow.h>
#include <OGL3D/Graphics/OGraphicsEngine.h> 
/*  #include 指令
#include 指令
作用：
將指定的標頭檔案內容插入到當前檔案中，以便使用標頭檔案中定義的類、函數或其他程式碼。
語法：
#include <標頭檔案>：表示從標準或全局路徑中搜尋檔案。
#include "標頭檔案"：表示從當前檔案所在目錄或指定的路徑中搜尋檔案。
*/
//#include <Windows.h>

OGame::OGame()
{
	m_graphicsEngine = std::make_unique<OGraphicsEngine>(); //初始化OGraphicsEngine,  || std::make_unique創建一個GraphicsEngine類型的智慧指標（std::unique_ptr）,並將其指派給變數m_graphicsEngine
	m_display = std::make_unique<OWindow>();                //使用智慧指針std::unique_ptr管理一個動態分配的OWindow對象，將其分配給成員變數m_display //使用make_unique<OWindow>()取代unique_ptr<OWindow>(new OWindow())

	m_display->makeCurrentContext();                        //調用OWindow類的makeCurrentContext()函數
}

OGame::~OGame()
{
}

void OGame::onCreate()
{

}

void OGame::onUpdate()
{
	m_graphicsEngine->clear(OVec4(1, 0, 0, 1));             //調用OGraphicsEngine類的clear函數，清除畫面OVec4(1, 0, 0, 1) 應該代表 RGBA 格式的紅色（紅色值為 1，綠色和藍色為 0，透明度為 1 即完全不透明）


	m_display->present(false);							    //調用OWindow類的present函數，將畫面顯示出來
}

void OGame::onQuit()
{
}



void OGame::quit()
{
	m_isRunning = false;
}
