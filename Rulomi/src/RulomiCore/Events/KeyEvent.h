#pragma once


#include "Event.h"



namespace Rulomi {

	class RULOMI_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)


	protected:
		int m_KeyCode;
		//���� 
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

	};


	//�����¼��̺��һ�в�������ͣ��Ȼ��һֱ��
	class RULOMI_API KeyPressedEvent : public KeyEvent
	{
	public: 
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		// ��д Event���е� һ���麯��&���麯��  override ��ʾ��д����
		//��Ϊʲô һ���麯���Ͳ��� ����д��ʱ����ǰ�棿����  virtual?
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "keyPressedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
		//// ��ͬ�� Hazel�� EVENT_CLASS_TYPE��
		//static EventType GetStaticType() { return EventType::KeyPressed; }
		////��д������EventClass�е��麯�������ó��麯�����������ö�̬
		////������ֻ��һ�� ָ��Event�� ָ���ʱ���ڱ�����ת��֮��ͨ����̬�����ҵ���ʵ�ʵ���Ϣ��
		//virtual EventType GetEventType() const override
		//{
		//	return GetStaticType();
		//}
		//virtual const char* GetName() const override 
		//{
		//	return "KeyPressed";
		//}

	private:
		int m_RepeatCount;				//��¼�û��˼���
	};

	//�밴���¼�����
	class RULOMI_API KeyReleaseEvent : public KeyEvent {
	public:
		KeyReleaseEvent(int keycode)
			: KeyEvent(keycode){}

		//debug ��
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	};

	//�����ַ�
	class RULOMI_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		//��ӡlog
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTypedEvent)
	};




}