#pragma once

#include  "RulomiCore/Layer.h"
#include "RulomiCore/Events/ApplicationEvent.h"
#include "RulomiCore/Events/MouseEvent.h"
#include "RulomiCore/Events/KeyEvent.h"

namespace Rulomi {


	class  RULOMI_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		//这个地方是 重写Layer里面的东西
		virtual void OnAttach() override ;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		//virtual void OnUpdate() override ;
		//virtual void OnEvent(Event& event)override;

		void Begin();
		void End();

	private:
		/*
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleaseEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		*/

	private:
		float m_time = 0.0f;

	};

}



