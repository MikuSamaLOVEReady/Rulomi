#include "RulomiPch.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include "Components.h"
#include "Entity.h"
#include "Renderer/Renderer2D.h"
#include <type_traits>

namespace Rulomi {

	Scene::Scene()
	{
	
		//TransformComponent transform;

		//registry 目的是管理所有的 components 与 entites
		//create  A valid entity identifier. （获取一个可用对象）
		//entt::entity entity = m_Registry.create();
		////<哪种componenrt,+初始化需要的值的类型>  （将这个component绑定到哪个entity身上+以及初始化每个entityComponent的参数）
		//m_Registry.emplace<TransformComponent>(entity);

		//class basic_view<Entity, exclude_t<>, Component>
		//.view的目的是 遍历所有的 <X>组件 并且将其对应的entity 提出来(每次只能查一种component)
		/*auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view) 
		{
			
		}*/

		//第一个参数是 包含的组件
		//第二参数是    不包含的组件
		//返回的 筛选出同时拥有 TransformComponent

		//entt::get<MeshComponent> 获得所有MeshComponets并且以list的形式表示
		//group中表示一个属性，而后的（形式参数又保存了两个参数） 表示筛选出同时拥有这三个属性的obj
		//
		//auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent, ASComponent>);
		//for (auto entity : group)
		//{
		//	//
		//	auto& position = group.get<TransformComponent>(entity);
		//	auto& [pos, ms] = group.get<TransformComponent, MeshComponent>(entity);
		//}

	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(),this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		return entity;
	}

	void Scene::DestoryEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	//Entity Scene::CreateEntity(const std::string& name)
	//{
	//	//Entity entity = ;
	//	//m_Registry.create();
	//	//return { m_Registry.create() , this };
	//}


	// <<Runtime>> OnUpdate submit
	void Scene::OnUpdate(TimeInterval ts)
	{
		//更新相机控制脚本
		{
			//each. 对每个entity views 都会调用这个lambda函数
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					// TODO: Move to Scene::OnScenePlay
					if (!nsc.spEntity)
					{
						// 在Bind的时候 InitialSpEntity（） 函数已经有所指向，现在调用才是正式创建
						nsc.spEntity = nsc.InitialSpEntity();
						//对其中包含的一般entity 赋值
						nsc.spEntity->entityID = Entity{ entity, this };
						// 因为
						nsc.spEntity->OnCreate();
					}
					nsc.spEntity->OnUpdate(ts);
				});
		}

		// Render 2D
		//获取到一组同时拥有俩组件的 entities
		//现在只是 设置了更新颜色
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;

		auto  view = m_Registry.view<TransformComponent, CameraComponent>();
		for (entt::entity per : view)
		{
			//每次取出这个 entity 的两个组件！！传递给render就可
			//get 返回的是一个含有 reference 的tuple
			auto [transform,cameraCop] = view.get<TransformComponent, CameraComponent>(per);
			if (cameraCop.main)
			{
				mainCamera = &cameraCop.camera;
				cameraTransform = transform.GetTransformMtx();
				break;
			}
		}
		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawSprite(transform.GetTransformMtx(), sprite, (int)entity);
			}
			// EndScene 
			Renderer2D::EndScene();
		}
	}

	void Scene::OnUpdateEditor(TimeInterval ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (entt::entity entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawSprite(transform.GetTransformMtx(), sprite, (int)entity);
		}
		Renderer2D::EndScene();
	}

	//全部 非FixAspecRatio的都需要更新 矩阵
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_viewport_width = width;
		m_viewport_height = height;
		//更新所有相机
		entt::basic_view view = m_Registry.view<CameraComponent>();
		for (entt::entity entity : view)
		{
			auto& Camera = view.get<CameraComponent>(entity);
			if (!Camera.AspectRatioFix)
			{
				Camera.camera.SetViewportSize(m_viewport_width, m_viewport_height);
			}
		}

	}

	Entity Scene::GetMainCamera()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (entt::entity entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.main)
				return Entity{ entity, this };
		}
		return {};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.camera.SetViewportSize(m_viewport_width, m_viewport_height);
	}
	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

}