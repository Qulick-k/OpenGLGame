#pragma once
#include <OGL3D/All.h>
#include "MyPlayer.h"

class MyGame: public OGame
{
public:
	MyGame();
	~MyGame();
	
	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);

private:
	f32 m_elapsedSeconds = 0.0f; // 用於儲存經過的時間
	MyPlayer* m_player = nullptr; // 用於儲存實體的指標
};

