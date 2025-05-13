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
	f32 m_elapsedSeconds = 0.0f; // �Ω��x�s�g�L���ɶ�
	OEntity* m_entity = nullptr; // �Ω��x�s���骺����
};

