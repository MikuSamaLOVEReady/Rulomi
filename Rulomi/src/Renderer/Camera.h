#pragma once
#include "glm/glm.hpp"


namespace Rulomi {

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection)
			:m_projectionMtx(projection) {};
		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const {
			return m_projectionMtx;
		}

	protected:
		glm::mat4 m_projectionMtx = glm::mat4(1.0f);

	};


}



