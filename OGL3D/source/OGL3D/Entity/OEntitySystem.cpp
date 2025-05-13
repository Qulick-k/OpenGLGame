#include <OGL3D/Entity/OEntitySystem.h>
#include <OGL3D/Entity/OEntity.h>

OEntitySystem::OEntitySystem()
{
}

OEntitySystem::~OEntitySystem()
{
}

bool OEntitySystem::createEntityInternal(OEntity* entity, size_t id)
{
	auto ptr = std::unique_ptr<OEntity>(entity);
	m_entities[id].emplace(entity, std::move(ptr));   //將entity和ptr的所有權轉移到map中
	
	entity->m_id = id; //設置entity的ID
	entity->m_entitySystem = this; //設置entity的entitySystem指標為當前的OEntitySystem實例

	entity->onCreate();                               //調用OEntity的onCreate()函數

	return true;
}

void OEntitySystem::removeEntity(OEntity* entity)
{
	m_entitiesToDestroy.emplace(entity); //將entity加入到m_entitiesToDestroy集合中
}

void OEntitySystem::update(f32 deltaTime)
{
	for (auto e : m_entitiesToDestroy)
	{
		m_entities[e->m_id].erase(e); //從m_enetities中刪除entity
	}
	m_entitiesToDestroy.clear(); //清空m_entitiesToDestroy集合

	for (auto&& [id, entities] : m_entities)
	{
		for (auto&& [ptr, entity] : entities)
		{
			entity->onUpdate(deltaTime); 
		}
	}
}
