#pragma once


namespace Rulomi {

	enum class RendererAPI
	{
		None = 0, OpenGL = 1, DX = 2 , Metel = 3
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};


}


