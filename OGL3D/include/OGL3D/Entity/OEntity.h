#pragma once
#include <OGL3D/OPrerequisites.h>

class OEntitySystem; // �e�V�ŧi OEntitySystem ���O
class OEntity
{
public:
	OEntity();
	virtual ~OEntity();

	void release();
	
	OEntitySystem* getEntitySystem();
protected:
	virtual void onCreate() {}
	virtual void onUpdate(f32 deltaTime) {}

protected:
	size_t m_id = 0; // �Ω��x�s���骺 ID
	OEntitySystem* m_entitySystem = nullptr; // �Ω��x�s����t�Ϊ�����

	friend class OEntitySystem; // �� OEntitySystem ���i�H�X�� OEntity ���p������
};

