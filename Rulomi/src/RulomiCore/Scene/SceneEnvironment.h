#pragma once
#include "Renderer/Texture.h"


namespace Rulomi {

	struct Environment
	{
		std::string FilePath;
		//���������
		Reference<TextureCube> RadianceMap;
		Reference<TextureCube> IrradianceMap;

		static Environment Load(const std::string& filepath);
	};;

}



