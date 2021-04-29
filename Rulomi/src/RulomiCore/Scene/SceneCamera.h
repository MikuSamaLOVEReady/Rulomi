#pragma once
#include "Renderer/Camera.h"

namespace Rulomi {

	//runtime camera ()
	class SceneCamera : public Camera
	{
	public:
		enum  class ProjectionType
		{
			perspective = 0, orthographic =1
		};
	public:
		SceneCamera();
		inline virtual ~SceneCamera() {};
		void SetOrthographic(float size, float nearClip, float farClip);

		//Field of View 用与显示内容范围
		void SetPerspective(float verticalFOV, float nearClip, float farClip);

		void SetViewportSize(uint32_t width, uint32_t height);

		void setProjectionType(ProjectionType type) { m_CameraType = type; RecalculateCamera();}
		ProjectionType GetCameraType() const { return m_CameraType; };

		// 正交
		float GetOrthographicSize() const { return m_OrthographicUnit; }
		float GetOrthographicNear() const { return m_OrthographicNear; }
		float GetOrthographicFar() const { return m_OrthographicFar; }
		void SetOrthographicNear(float Near)  {  m_OrthographicNear = Near; RecalculateCamera(); }
		void SetOrthographicFar(float Far)  {  m_OrthographicFar = Far; RecalculateCamera(); }
		void SetOrthographicSize(float Size) { m_OrthographicUnit = Size; RecalculateCamera(); }

		//透视投影
		float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
		void SetPerspectiveVerticalFOV(float verticalFov) { m_PerspectiveFOV = verticalFov; RecalculateCamera(); }
		float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; RecalculateCamera(); }
		float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		void SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; RecalculateCamera(); }


	private:
		void RecalculateCamera();
	private:
		float m_OrthographicUnit = 10.0f;

		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;
		float m_AspectRatio = 0.0f;

		//弧度制
		float m_PerspectiveFOV = glm::radians(60.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

		ProjectionType m_CameraType = ProjectionType::orthographic;


	};



}


