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
	f32 m_elapsedSeconds = 0.0f; // �Ω��x�s�g�L���ɶ�
	MyPlayer* m_player = nullptr; // �Ω��x�s���骺����
};

