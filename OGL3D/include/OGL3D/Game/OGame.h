#pragma once
#include <memory>

class OGraphicsEngine;
class OWindow;
class OGame
{
public:
	OGame();
	~OGame();

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onQuit();

	void run();
	void quit();
protected:
	bool m_isRunning = true;
	std::unique_ptr<OGraphicsEngine> m_graphicsEngine; //定義名為 m_graphicsEngine 指向 OGraphicsEngine 類型的智慧指針
	std::unique_ptr<OWindow> m_display;                //定義名為 m_display 指向 OWindow 類型的智慧指針, 來取代OWindow* m_display = nullptr
};

