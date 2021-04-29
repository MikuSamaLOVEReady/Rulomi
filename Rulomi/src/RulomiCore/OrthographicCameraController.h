#pragma once
#include "Core.h"
#include "Renderer/OrthographicCamera.h"
#include "Core/Timeinternal.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace Rulomi {

	class OrthographicCameraController
	{
	public:
		//提供 缩放功能 zoom in/out
		OrthographicCameraController(float aspectRation);

		//
		void OnUpdate(TimeInterval deltTime);
		void OnEvent(Event& e);
		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_OrtCamera; };
	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		//wrap一个相机
		OrthographicCamera m_OrtCamera;
		glm::vec3 m_CameraPostion = { 0.0f , 0.0f , 0.0f };
		float m_CameraMoveSpeed = 1.0f;
		float m_CameraRotationDegree = 0.0f;
		float m_CameraRotationSpeed = 8.0f;

	};



}


