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

		//相机的位置和角度决定 view matirx
		const  glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		//投射矩阵只在 perspective 投影中有用
		const  glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		//直接
		const glm::mat4& GetVPMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateMatrix();

	private:
		//设置相机默认初始位置
		glm::vec3 m_postion = { 0.0f , 0.0f, 0.0f };
		float m_Rotation = 0.0f;

		// M  VP 中的VP由相机算出
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		//由于每一帧相机位置是不变的
		glm::mat4 m_ViewProjectionMatrix;

	};

}




