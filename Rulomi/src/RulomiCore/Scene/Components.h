#pragma once

#include <glm/glm.hpp>
#include "Renderer/Camera.h"
#include "SceneCamera.h"
#include "ScriptableEntity.h"
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


namespace Rulomi {

		//wrapper//��transform ������뿪
		struct  TransformComponent 
		{
			glm::vec3 position = { 0.0f,0.0f,0.0f };
			//euler angles (pitch, yaw, roll), ��x,y,z�� in radians
			glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
			glm::vec3 scale      = { 1.0f,1.0f,1.0f };

		  
			TransformComponent() = default;
			//�������캯��( Ĭ�� bit copy)
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const glm::vec3& translate)
				: position(translate) {}

			glm::mat4 GetTransformMtx() const 
			{
					
				glm::mat4 rota =  glm::toMat4(glm::quat(rotation));

				return glm::translate(glm::mat4(1.0f), position)
					* rota
					* glm::scale(glm::mat4(1.0f), scale);
			}

			//Ĭ������ת��
			//operator const glm::mat4& () const { return Transform; }
		};

		//���������Ҳ�ɽ���ɫ���
		struct SpriteRendererComponent
		{
			glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

			SpriteRendererComponent() = default;
			SpriteRendererComponent(const SpriteRendererComponent&) = default;
			SpriteRendererComponent(const glm::vec4& color)
				: Color(color) {}
		};

		//������
		struct TagComponent
		{
			std::string Tag;

			TagComponent() = default;
			TagComponent(const TagComponent&) = default;
			TagComponent(const std::string& tag)
				: Tag(tag) {}
		};

		//
		struct CameraComponent
		{
			SceneCamera camera;
			bool main = true;  //Ĭ�����������--->ÿ����ӵ�ʱ��ע������
			bool AspectRatioFix = false; // ()���ǹ̶���������ʾ projection mat��Ҫ����

			CameraComponent() = default;
			CameraComponent(const CameraComponent&) = default;
		    //projectionMat ��������� SceneCamere�ĳ�ʼ��
			//CameraComponent(const glm::mat4&projectionMat)
			//	: camera(projectionMat) {}
		};


		// taking a type  ����һ���ű� Entity
		struct NativeScriptComponent
		{
			ScriptableEntity* spEntity;

			//����ָ��  �������� + ����ָ���� + ����
			ScriptableEntity* (*InitialSpEntity)();
			void (*DeleteSpEntity)(NativeScriptComponent*);

			//���ʱ��
			template <typename T>
			// ͨ��bind---> Ϊ����ָ�븳ֵ
			void Bind()
			{
				//�ڳ�ʼ��֮������ת�͵����࣬������д���麯�� �� create update delete �ܱ�vtable �ҵ�

				// labda�Ǹ���������ֻ���� ����ָ����ָ���������
				InitialSpEntity = []() {return static_cast<ScriptableEntity*>(new T()); };
				DeleteSpEntity = [](NativeScriptComponent* nsc) {delete nsc->spEntity; nsc->spEntity = nullptr; };
			}

		};





}


