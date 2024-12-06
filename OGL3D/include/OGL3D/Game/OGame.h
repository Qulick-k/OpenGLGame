#pragma once
#include <memory>

class OWindow;
class OGame
{
public:
	OGame();
	~OGame();

	void run();
	void quit();
protected:
	bool m_isRunning = true;
	std::unique_ptr<OWindow> m_display;           //�w�q�W�� m_display ���V OWindow ���������z���w, �Ө��NOWindow* m_display = nullptr
};

