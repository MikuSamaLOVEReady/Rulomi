#pragma once
#include "Scene.h"
#include "entt.hpp"


//can not include entity in scene 
namespace Rulomi {

	// 其本质是一个wrapper class
	class Entity
	{
	public:
		Entity() = default;

		//这个entity被唯一标识的ID 
		//Entity(entt::entity handle, Scene* scene);
		Entity(entt::entity m_Entityid, Scene* m_Scene);
		//	Entity(const Entity& other) = default;//TODO: 等改回weak pointer的时候修改

		//weird
		template<typename T, typename...Args>
		T& AddComponent(Args&&... args)
		{
			//不能重复给一个obj addcomponent
			RLM_ASSERT(!HasComponet<T>(), "Entity component exist already");
			//args 用于初始化这个组件  forword 表示把 传递的参数不做操作而是将引用继续传递
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityID, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			RLM_ASSERT(HasComponet<T>(), "Entity component not exist");
			// brief Returns references to the given components for an entity. 
			// （可同时获取多个组件)
			return m_Scene->m_Registry.get<T>(m_EntityID);
		}

		template <typename T>
		void  RemoveComponent()
		{
			RLM_ASSERT(HasComponet<T>(), "Entity component not exist");
			m_Scene->m_Registry.remove<T>(m_EntityID);
		}

		//查找此entity 是否有这个组件
		template<typename T>
		bool HasComponet()
		{
			//has->all_of
			return m_Scene->m_Registry.all_of<T>(m_EntityID);
		}

		operator bool() const { return m_EntityID != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityID; }
		operator entt::entity() const { return m_EntityID; }

		//比较两个entity是否相同
		bool operator==(const Entity& other) const
		{
			return m_EntityID == other.m_EntityID;
		}
		bool operator!=(const Entity& other)const
		{
			//这里的==会调用上面的重写
			return  !(*this == other);
		}


	
	private:
		//为什么叫handle？他本质是这个Entity的ID 
		entt::entity m_EntityID { entt::null };
		//本质是一个weak_ptr
		Scene* m_Scene = nullptr;
		


	};

}


