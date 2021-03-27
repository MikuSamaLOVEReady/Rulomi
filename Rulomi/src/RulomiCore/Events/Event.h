#pragma once

#include"RulomiPch.h"
#include "RulomiCore/Core.h"



namespace Rulomi {

	//
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTypedEvent,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};


	//������ bit��ʾ�Ļ�ÿ������ ֻռ��һλ ����mask xor�����ְ�λ����
	//����ط��Ͳ���class wtf�� ����������ô
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BITMove(0),
		EventCategoryInput = BITMove(1),
		EventCategoryKeyboard = BITMove(2),
		EventCategoryMouse = BITMove(3),
		EventCategoryMouseButton = BITMove(4)
	};

// 
#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::##type; } \
                                                         virtual EventType GetEventType() const override{return GetStaticType();}\
                                                         virtual const char* GetName() const override {return #type;}

	//������������ȷʵ��֪
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

	//friend class ���Է��� protected & private
	class RULOMI_API Event
	{
		//friend class EventDispatcher;
	public:
		bool Handled = false;

		//��ȡ�������ͺ�  ����
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual const char* GetName() const = 0;
		//  std::string��һ�� = ����д�˴Ӷ��� const char* ���͸�ֵ std::strings
		//  ������� һ���麯��������Ԥ���趨�õ� ���壩 ���������������������͵ü��� override����д��
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	};

	//event������(ÿ���¼�һ����) ������ཫ���������¼����ݳ�ȥ
	class EventDispatcher {
		//EventFn �Ǵ����ӦEventtype�ĺ���  T ���κ�һ��EventType  
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event)
		{

		}

		//Dispatch ������һ��ģ�庯�� ��Ҫָ�����ͣ���
		// func �Ǵ������event�ĺ��������ҷ���ֵ�� bool
		//���� funcָ�� ����������
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			//  ����ط���T �Ƕ�Ӧ ��������(event������)' ������ 
			if (m_Event.GetEventType() == T::GetStaticType() ) 
			{
				//ȡ�����event �ĵ�ַ��ָ�룩 ��������ת�͵���ȷ��event���ͣ���Ȼ��ָ�룩
				//����ָ�� �õ�reference
				//��Ϊ�������if �Ѿ��жϹ�����ط��ܷ�ת��
				// ֮�� ��event ���ݸ������������func�� ��������������
				m_Event.Handled = func(*(T*)&m_Event);
					return true;
			}
			return false;
		}

	private:
		//����Ǹ����� ����
		Event& m_Event;

	};


	//����һ�� << ΪLogϵͳ����  Log  ����һ���ǳ�Ա���� (û��Ĭ�϶���this, ����Ҫ����)
	inline std::ostream& operator << (std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}

