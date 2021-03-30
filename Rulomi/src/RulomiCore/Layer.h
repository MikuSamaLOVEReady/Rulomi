#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Core/Timeinternal.h"
namespace Rulomi {

	class RULOMI_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		//一般虚函数 默认没效果。
		virtual void OnAttach() {};
		virtual void OnDetach() {};
		//virtual void OnUpdate() {};
		virtual void OnUpdate(TimeInterval ts) {}
		virtual void OnImGuiRender() {};
		//layer 的事件处理
		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() const { return m_DebugName; }

	private :
		std::string m_DebugName;
	};

}


