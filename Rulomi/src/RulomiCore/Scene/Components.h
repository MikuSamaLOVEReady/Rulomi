#pragma once

#include <glm/glm.hpp>
#include "Renderer/Camera.h"
#include "SceneCamera.h"
#include "ScriptableEntity.h"
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>


namespace Rulomi {

		//wrapper//将transform 组件分离开
		struct  TransformComponent 
		{
			glm::vec3 position = { 0.0f,0.0f,0.0f };
			//euler angles (pitch, yaw, roll), （x,y,z） in radians
			glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
			glm::vec3 scale      = { 1.0f,1.0f,1.0f };

		  
			TransformComponent() = default;
			//拷贝构造函数( 默认 bit copy)
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

			//默认类型转换
			//operator const glm::mat4& () const { return Transform; }
		};

		//纹理组件、也可叫颜色组件
		struct SpriteRendererComponent
		{
			glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

			SpriteRendererComponent() = default;
			SpriteRendererComponent(const SpriteRendererComponent&) = default;
			SpriteRendererComponent(const glm::vec4& color)
				: Color(color) {}
		};

		//标记组件
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
			bool main = true;  //默认是主相机。--->每次添加的时候注意设置
			bool AspectRatioFix = false; // ()不是固定长宽比则表示 projection mat需要更新

			CameraComponent() = default;
			CameraComponent(const CameraComponent&) = default;
		    //projectionMat 计算放在了 SceneCamere的初始化
			//CameraComponent(const glm::mat4&projectionMat)
			//	: camera(projectionMat) {}
		};


		// taking a type  包含一个脚本 Entity
		struct NativeScriptComponent
		{
			ScriptableEntity* spEntity;

			//函数指针  返回类型 + 函数指针名 + 参数
			ScriptableEntity* (*InitialSpEntity)();
			void (*DeleteSpEntity)(NativeScriptComponent*);

			//这个时候
			template <typename T>
			// 通过bind---> 为函数指针赋值
			void Bind()
			{
				//在初始化之后，向上转型到父类，保留重写的虚函数 即 create update delete 能被vtable 找到

				// labda是个函数，绑定只是让 函数指针能指向这个函数
				InitialSpEntity = []() {return static_cast<ScriptableEntity*>(new T()); };
				DeleteSpEntity = [](NativeScriptComponent* nsc) {delete nsc->spEntity; nsc->spEntity = nullptr; };
			}

		};





}


