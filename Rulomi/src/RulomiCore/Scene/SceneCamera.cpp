#include"RulomiPch.h"
#include "SceneCamera.h"
#include <glm/gtc/matrix_transform.hpp>


namespace Rulomi {

	SceneCamera::SceneCamera()
	{
		RecalculateCamera();
	}


	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_CameraType = ProjectionType::orthographic;
		m_OrthographicUnit = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;
		RecalculateCamera();
	}

	void SceneCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
	{
		m_CameraType = ProjectionType::perspective;
		m_PerspectiveFOV = verticalFOV;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;
		RecalculateCamera();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateCamera();
	}

	void SceneCamera::RecalculateCamera()
	{
		if (m_CameraType == ProjectionType::orthographic)
		{
			float m_OrthographicL = -m_AspectRatio * m_OrthographicUnit * 0.5;
			float m_OrthographicR = m_AspectRatio * m_OrthographicUnit * 0.5;
			float m_OrthographicB = -m_OrthographicUnit * 0.5;
			float m_OrthographicT = m_OrthographicUnit * 0.5;
			m_projectionMtx = glm::ortho(m_OrthographicL, m_OrthographicR, m_OrthographicB, m_OrthographicT, m_OrthographicNear, m_OrthographicFar);
		}
		else
		{
			//m_PerspectiveFOV 只接受弧度制
			m_projectionMtx = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
		}
	

	}



}