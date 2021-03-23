#include <Rulomi.h>

#include "glm/glm.hpp"
#include "imgui/imgui.h"


class Exmplayer :public Rulomi::Layer {
public:
	Exmplayer()
		:Layer("MikuSama")
	{

	 }

	void OnUpdate() override
	{
		//RLM_Client_TRACE("Exmplayer UPDATA");

		if (Rulomi::Input::IsKeyPressed(RLM_KEY_BACKSPACE))
			RLM_Client_INFO("RLM_KEY_BACKSPACE ！！！！！！！！！！！！！！！！");
	}

	void OnEvent(Rulomi::Event& event) override
	{
		//RLM_Client_TRACE("{0} Layer EVENT By Exmplayer ", event);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("WWWWW");
		ImGui::Text("MIKU SAMA");
		ImGui::End();
	}


};


class Sandbox : public Rulomi::Application {

public:
	Sandbox() {

		PushLayer(new Exmplayer());
		//PushOverlay(new Rulomi::ImGuiLayer());

	}

	~Sandbox() {

	}

};

//引擎内部的函数的申明 由游戏对象定义
Rulomi::Application* Rulomi::CreateApplication()
{
	return new Sandbox();
}


