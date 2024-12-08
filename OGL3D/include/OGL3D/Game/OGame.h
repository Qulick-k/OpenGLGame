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
	std::unique_ptr<OGraphicsEngine> m_graphicsEngine; //�w�q�W�� m_graphicsEngine ���V OGraphicsEngine ���������z���w
	std::unique_ptr<OWindow> m_display;                //�w�q�W�� m_display ���V OWindow ���������z���w, �Ө��NOWindow* m_display = nullptr
};

