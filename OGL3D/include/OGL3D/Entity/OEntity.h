#pragma once
#include <OGL3D/OPrerequisites.h>

class OEntitySystem; // 前向宣告 OEntitySystem 類別
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
	size_t m_id = 0; // 用於儲存實體的 ID
	OEntitySystem* m_entitySystem = nullptr; // 用於儲存實體系統的指標

	friend class OEntitySystem; // 讓 OEntitySystem 類可以訪問 OEntity 的私有成員
};

