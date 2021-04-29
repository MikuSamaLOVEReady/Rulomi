#pragma once

#include <glm/glm.hpp>

namespace Rulomi {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position)
		{
			m_postion = position;
			RecalculateMatrix();
		}
		const glm::vec3& GetPosition() const
		{
			return m_postion;
		}

		void SetRotation(float rotation)
		{
			m_Rotation = rotation;
			RecalculateMatrix();
		}

		void SetProjection(float left, float right, float bottom, float top);

		float GetRotation() const { return m_Rotation; }

		//�����λ�úͽǶȾ��� view matirx
		const  glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		//Ͷ�����ֻ�� perspective ͶӰ������
		const  glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		//ֱ��
		const glm::mat4& GetVPMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateMatrix();

	private:
		//�������Ĭ�ϳ�ʼλ��
		glm::vec3 m_postion = { 0.0f , 0.0f, 0.0f };
		float m_Rotation = 0.0f;

		// M  VP �е�VP��������
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		//����ÿһ֡���λ���ǲ����
		glm::mat4 m_ViewProjectionMatrix;

	};

}




