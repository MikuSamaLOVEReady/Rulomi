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

		//registry Ŀ���ǹ������е� components �� entites
		//create  A valid entity identifier. ����ȡһ�����ö���
		//entt::entity entity = m_Registry.create();
		////<����componenrt,+��ʼ����Ҫ��ֵ������>  �������component�󶨵��ĸ�entity����+�Լ���ʼ��ÿ��entityComponent�Ĳ�����
		//m_Registry.emplace<TransformComponent>(entity);

		//class basic_view<Entity, exclude_t<>, Component>
		//.view��Ŀ���� �������е� <X>��� ���ҽ����Ӧ��entity �����(ÿ��ֻ�ܲ�һ��component)
		/*auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view) 
		{
			
		}*/

		//��һ�������� ���������
		//�ڶ�������    �����������
		//���ص� ɸѡ��ͬʱӵ�� TransformComponent

		//entt::get<MeshComponent> �������MeshComponets������list����ʽ��ʾ
		//group�б�ʾһ�����ԣ�����ģ���ʽ�����ֱ��������������� ��ʾɸѡ��ͬʱӵ�����������Ե�obj
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
		//����������ƽű�
		{
			//each. ��ÿ��entity views ����������lambda����
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					// TODO: Move to Scene::OnScenePlay
					if (!nsc.spEntity)
					{
						// ��Bind��ʱ�� InitialSpEntity���� �����Ѿ�����ָ�����ڵ��ò�����ʽ����
						nsc.spEntity = nsc.InitialSpEntity();
						//�����а�����һ��entity ��ֵ
						nsc.spEntity->entityID = Entity{ entity, this };
						// ��Ϊ
						nsc.spEntity->OnCreate();
					}
					nsc.spEntity->OnUpdate(ts);
				});
		}

		// Render 2D
		//��ȡ��һ��ͬʱӵ��������� entities
		//����ֻ�� �����˸�����ɫ
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;

		auto  view = m_Registry.view<TransformComponent, CameraComponent>();
		for (entt::entity per : view)
		{
			//ÿ��ȡ����� entity ����������������ݸ�render�Ϳ�
			//get ���ص���һ������ reference ��tuple
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

	//ȫ�� ��FixAspecRatio�Ķ���Ҫ���� ����
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_viewport_width = width;
		m_viewport_height = height;
		//�����������
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