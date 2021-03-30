#include "RulomiPch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>



namespace Rulomi {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


	void OrthographicCamera::RecalculateMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_postion);
		//��λ�ƾ�����rotation ������ 0,0,1 Ϊ��
		transform = glm::rotate(transform, glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		//transform �Ƕ���������в�����������Ĳ�������Ҫȡ��
		m_ViewMatrix = glm::inverse( transform );
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}



}