#include "RulomiPch.h"
#include "OrthographicCameraController.h"
#include "Input.h"

#include "Keycodes.h"

namespace Rulomi {
	

	OrthographicCameraController::OrthographicCameraController(float aspectRation)
		:m_AspectRatio(aspectRation), m_OrtCamera(-m_AspectRatio*m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
	}

	void OrthographicCameraController::OnUpdate(TimeInterval deltTime)
	{
		//��ǰ��Щ���� �Ǹ��� ��ǰ��֡��������
		//Ӧ������Ϊ ��Time
		if (Rulomi::Input::IsKeyPressed(RLM_KEY_A))
			m_CameraPostion.x -= m_CameraMoveSpeed * deltTime;
		else if (Rulomi::Input::IsKeyPressed(RLM_KEY_D))
			m_CameraPostion.x += m_CameraMoveSpeed * deltTime;
		if (Rulomi::Input::IsKeyPressed(RLM_KEY_W))
			m_CameraPostion.y += m_CameraMoveSpeed * deltTime;
		else if (Rulomi::Input::IsKeyPressed(RLM_KEY_S))
			m_CameraPostion.y -= m_CameraMoveSpeed * deltTime;
		m_OrtCamera.SetPosition(m_CameraPostion); 

		if (Rulomi::Input::IsKeyPressed(RLM_KEY_Q))
			m_CameraRotationDegree += m_CameraRotationSpeed * deltTime;
		if (Rulomi::Input::IsKeyPressed(RLM_KEY_E))
			m_CameraRotationDegree -= m_CameraRotationSpeed * deltTime;
		m_OrtCamera.SetRotation(m_CameraRotationDegree);

	}

	
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher cameraDispater(e);
		cameraDispater.Dispatch<WindowResizeEvent> ( std::bind(&OrthographicCameraController::OnWindowResize, this, std::placeholders::_1) );
		cameraDispater.Dispatch<MouseScrolledEvent> (RLM_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));

	}

	//ͨ���ı� �����Aspect ratio���ı�����
	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.Getwidth() / (float)e.Getheight();
		m_OrtCamera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	// �����Ǹı䴰��
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYoffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		RLM_CORE_WARN("OFFSETY {0}  {1}", e.GetYoffset(), e.GetXoffset());
		m_OrtCamera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;

	}

	//����viewport��С�ı��
	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_OrtCamera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

}