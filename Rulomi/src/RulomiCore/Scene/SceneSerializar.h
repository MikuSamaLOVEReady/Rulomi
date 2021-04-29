#pragma once
#include "Scene.h"


namespace Rulomi {
	class SceneSerializar
	{
	public:
		SceneSerializar(const Reference<Scene>& scene);
		 
		void Serialize(const std::string& filepath);

		
		bool DeSerialize(const std::string& filepath);

	private:
		Reference<Scene> m_Scene;

	};

}


