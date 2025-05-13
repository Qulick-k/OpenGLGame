#pragma once
#include <OGL3D/All.h>

class MyPlayer : public OEntity
{
public:
	MyPlayer();
	~MyPlayer();

	virtual void onCreate();
	virtual void onUpdate(f32 deltaTime);

private:
	f32 m_elapsedSeconds = 0.0f; // 用於儲存經過的時間
	OEntity* m_entity = nullptr; // 用於儲存實體的指標
};

