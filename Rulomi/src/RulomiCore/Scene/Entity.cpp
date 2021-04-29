#include "RulomiPch.h"
#include "Entity.h"


namespace Rulomi {

	Entity::Entity(entt::entity m_Entityid, Scene* m_Scene)
		:m_EntityID(m_Entityid), m_Scene(m_Scene)
	{
	}

}