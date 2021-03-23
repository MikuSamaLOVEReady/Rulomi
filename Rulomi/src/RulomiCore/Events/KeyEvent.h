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
		//这样 
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

	};


	//处理按下键盘后的一切操作，有停滞然后一直按
	class RULOMI_API KeyPressedEvent : public KeyEvent
	{
	public: 
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		// 重写 Event类中的 一般虚函数&纯虚函数  override 表示重写他俩
		//但为什么 一般虚函数就不用 再重写的时候在前面？？？  virtual?
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "keyPressedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
		//// 等同于 Hazel的 EVENT_CLASS_TYPE宏
		//static EventType GetStaticType() { return EventType::KeyPressed; }
		////重写的两个EventClass中的虚函数，设置成虚函数有利于利用多态
		////当我们只有一个 指向Event的 指针的时候（在被向上转型之后，通过动态绑定能找到它实际的信息）
		//virtual EventType GetEventType() const override
		//{
		//	return GetStaticType();
		//}
		//virtual const char* GetName() const override 
		//{
		//	return "KeyPressed";
		//}

	private:
		int m_RepeatCount;				//记录敲击了几次
	};

	//与按下事件相似
	class RULOMI_API KeyReleaseEvent : public KeyEvent {
	public:
		KeyReleaseEvent(int keycode)
			: KeyEvent(keycode){}

		//debug 用
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	};

	//输入字符
	class RULOMI_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		//打印log
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTypedEvent)
	};




}