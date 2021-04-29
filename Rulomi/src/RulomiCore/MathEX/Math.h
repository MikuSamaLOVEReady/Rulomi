#pragma once

#include <glm/glm.hpp>


namespace Rulomi {

	namespace Math {

		//½âÎö¾ØÕó
		bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
	}




}