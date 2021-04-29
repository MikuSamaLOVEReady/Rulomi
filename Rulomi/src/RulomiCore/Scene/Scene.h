#pragma once
#include "entt.hpp"
#include  "RulomiCore/Core/Timeinternal.h"
#include "Renderer/EditorCamera.h"


namespace Rulomi {
	
	//前向声明 
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		//这个就是单纯申请一个ID
		Entity CreateEntity(const std::string& name);
		void DestoryEntity(Entity entity);

		//Runtime Update
		void OnUpdate(TimeInterval ts);
		void OnUpdateEditor(TimeInterval ts, EditorCamera& camera);


		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetMainCamera();

	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		//Registy contains actual components data & entity ID
		entt::registry m_Registry;

		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class SceneSerializar;
		uint32_t m_viewport_width = 0.0f , m_viewport_height = 0.0f;
	};


}