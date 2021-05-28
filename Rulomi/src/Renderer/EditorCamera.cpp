#include "RulomiPch.h"
#include "EditorCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "RulomiCore/Input.h"
#include "RulomiCore/Keycodes.h"
#include "RulomiCore/MouseButtonKeycode.h"



#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Rulomi {
	//initial list ���������ʵ��������
	EditorCamera::EditorCamera(float fov, float aspectration, float nearClip, float FarClip)
		:m_FOV(fov), m_AspectRatio(aspectration), m_NearClip(nearClip), m_FarClip(FarClip), Camera(glm::perspective(glm::radians(m_FOV), aspectration, nearClip, FarClip))
	{
		UpdateView();
	}

	void EditorCamera::OnUpdate(TimeInterval ts)
	{
		if (Input::IsKeyPressed(RLM_KEY_LEFT_ALT))
		{
			const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
			//����ÿһ֡��λ�øı��� ����ͨ������λ�����ṩ������ǰ������ x λ�� �� y λ�ƣ�
			glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.005f;
			m_InitialMousePosition = mouse;
			//�м�� Delete
			if (Input::IsMouseButtonPressed(RLM_MOUSE_BUTTON_LEFT))
				MouseRotate(delta);
			else if (Input::IsMouseButtonPressed(RLM_MOUSE_BUTTON_RIGHT))
				MouseZoom(delta.y);
		}
		UpdateView();
	}

	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(RLM_BIND_EVENT_FN(EditorCamera::OnMouseScroll));
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& e)
	{
		float delta = e.GetYoffset() * 0.1f;
		MouseZoom(delta);
		UpdateView();
		return false;
	}



	//�۲������ ֻ��������ת
	void EditorCamera::MouseRotate(const glm::vec2& delta)
	{
		//float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		//y ��  
		m_Yaw +=  delta.x * 0.8f;
		//x ��
		m_Pitch += delta.y * 0.8f;
	}

	//��ǰ GetForwardDirection ����
	void EditorCamera::MouseZoom(float delta)
	{
		m_Distance -= delta * ZoomSpeed();
		if (m_Distance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_Distance = 1.0f;
		}
	}

	//zoom �ٶ��������ǰ�����й�
	float EditorCamera::ZoomSpeed() const
	{
		float distance = m_Distance * 0.3f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f); 

		return speed;
	}


	//Update����� ViewMtx
	void EditorCamera::UpdateView()
	{
		// m_Pitch  m_Yaw ����
		m_Position = CalculatePosition();
		glm::quat orientation = GetOrientation();
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	//������Ӧ viewport��С�仯���� ProjectMtx
	void EditorCamera::UpdateProjection()
	{
		m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
		m_projectionMtx = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
	}

	// m_Distance
	glm::vec3 EditorCamera::CalculatePosition() const
	{
		return  m_FocalPoint - GetForwardDirection() * m_Distance;
	}

	//
	glm::vec3 EditorCamera::GetUpDirection() const
	{
		// ��δ�quat����ȡ ĳ����ĳ����أ�
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	//��ȡ����ƶ�����
	glm::vec3 EditorCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::quat EditorCamera::GetOrientation() const
	{
		//���quant��û��w��ֵ������ԭ��ľ��룩
		return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
	}
	
}