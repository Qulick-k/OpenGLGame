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
	std::unique_ptr<OWindow> m_display;           //定義名為 m_display 指向 OWindow 類型的智慧指針, 來取代OWindow* m_display = nullptr
};

