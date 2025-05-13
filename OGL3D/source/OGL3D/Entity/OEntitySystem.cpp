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
	m_entities[id].emplace(entity, std::move(ptr));   //�Nentity�Mptr���Ҧ��v�ಾ��map��
	
	entity->m_id = id; //�]�mentity��ID
	entity->m_entitySystem = this; //�]�mentity��entitySystem���Ь���e��OEntitySystem���

	entity->onCreate();                               //�ե�OEntity��onCreate()���

	return true;
}

void OEntitySystem::removeEntity(OEntity* entity)
{
	m_entitiesToDestroy.emplace(entity); //�Nentity�[�J��m_entitiesToDestroy���X��
}

void OEntitySystem::update(f32 deltaTime)
{
	for (auto e : m_entitiesToDestroy)
	{
		m_entities[e->m_id].erase(e); //�qm_enetities���R��entity
	}
	m_entitiesToDestroy.clear(); //�M��m_entitiesToDestroy���X

	for (auto&& [id, entities] : m_entities)
	{
		for (auto&& [ptr, entity] : entities)
		{
			entity->onUpdate(deltaTime); 
		}
	}
}
