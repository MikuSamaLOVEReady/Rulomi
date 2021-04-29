#pragma once

#include  "Camera.h"
#include "RulomiCore/Core/Timeinternal.h"
#include "RulomiCore/Events/Event.h"
#include "RulomiCore/Events/MouseEvent.h"
#include "glm/glm.hpp"
 

namespace Rulomi {

	//编辑者3D相机  主要控制 ViewMtx  //projectMtx 在初始化时定死
	class EditorCamera :public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectration, float nearClip, float FarClip);

		void OnUpdate(TimeInterval ts);
		void OnEvent(Event& e);

		inline void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

		glm::quat  GetOrientation() const;
		glm::vec3 GetForwardDirection() const;
		glm::vec3 GetUpDirection() const;

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetViewProjection() const { return m_projectionMtx * m_ViewMatrix; }

	private:
		//更新 viewMtx
		void UpdateView();
		//虽然在初始化的时候 为ProjectMtx赋值过了
		void UpdateProjection();

		//
		bool OnMouseScroll(MouseScrolledEvent& e);

		glm::vec3 CalculatePosition() const;

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);
		float ZoomSpeed() const;

		//aspect default 16:9
		float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		//Look at point
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };
		//距离所观察的点的位置
		float m_Distance = 10.0f;
		// x y两个轴的 rotate的角度（弧度制）
		float m_Pitch = 0.0f, m_Yaw = 0.0f;

		//鼠标的起始位置
		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };
		//viewMatrix
		glm::mat4 m_ViewMatrix;
		float m_ViewportWidth = 1280, m_ViewportHeight = 720;

	};



}


