#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Rulomi {

	class RULOMI_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		//һ���麯�� Ĭ��ûЧ����
		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnImGuiRender() {};
		//layer ���¼�����
		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() const { return m_DebugName; }

	private :
		std::string m_DebugName;
	};

}


