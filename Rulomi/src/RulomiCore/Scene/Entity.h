#pragma once
#include "Scene.h"
#include "entt.hpp"


//can not include entity in scene 
namespace Rulomi {

	// �䱾����һ��wrapper class
	class Entity
	{
	public:
		Entity() = default;

		//���entity��Ψһ��ʶ��ID 
		//Entity(entt::entity handle, Scene* scene);
		Entity(entt::entity m_Entityid, Scene* m_Scene);
		//	Entity(const Entity& other) = default;//TODO: �ȸĻ�weak pointer��ʱ���޸�

		//weird
		template<typename T, typename...Args>
		T& AddComponent(Args&&... args)
		{
			//�����ظ���һ��obj addcomponent
			RLM_ASSERT(!HasComponet<T>(), "Entity component exist already");
			//args ���ڳ�ʼ��������  forword ��ʾ�� ���ݵĲ��������������ǽ����ü�������
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			RLM_ASSERT(HasComponet<T>(), "Entity component not exist");
			// brief Returns references to the given components for an entity. 
			// ����ͬʱ��ȡ������)
			return m_Scene->m_Registry.get<T>(m_EntityID);
		}

		template <typename T>
		void  RemoveComponent()
		{
			RLM_ASSERT(HasComponet<T>(), "Entity component not exist");
			m_Scene->m_Registry.remove<T>(m_EntityID);
		}

		//���Ҵ�entity �Ƿ���������
		template<typename T>
		bool HasComponet()
		{
			//has->all_of
			return m_Scene->m_Registry.all_of<T>(m_EntityID);
		}

		operator bool() const { return m_EntityID != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityID; }
		operator entt::entity() const { return m_EntityID; }

		//�Ƚ�����entity�Ƿ���ͬ
		bool operator==(const Entity& other) const
		{
			return m_EntityID == other.m_EntityID;
		}
		bool operator!=(const Entity& other)const
		{
			//�����==������������д
			return  !(*this == other);
		}


	
	private:
		//Ϊʲô��handle�������������Entity��ID 
		entt::entity m_EntityID { entt::null };
		//������һ��weak_ptr
		Scene* m_Scene = nullptr;
		


	};

}


