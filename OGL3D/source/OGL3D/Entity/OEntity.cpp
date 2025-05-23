#include <OGL3D/Entity/OEntity.h>
#include <OGL3D/Entity/OEntitySystem.h>

OEntity::OEntity()
{
}

OEntity::~OEntity()
{
}

void OEntity::release()
{
	m_entitySystem->removeEntity(this); //從OEntitySystem中移除當前實例
}

OEntitySystem* OEntity::getEntitySystem()
{
	return m_entitySystem;
}
