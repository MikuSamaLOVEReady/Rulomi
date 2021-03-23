#pragma once


#include "Event.h"

namespace Rulomi {

	class RULOMI_API MouseMovedEvent : public Event
	{
	public:
		//constructor  Ϊʲô���ﲻ���óɵ���
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {};

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoved:  "<<"x: "<< m_MouseX << "y: " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX , m_MouseY;

	};

	class RULOMI_API MouseScrolledEvent : public Event 
	{

	public:
		MouseScrolledEvent(float xoffset , float yoffset)
			:m_Xoffset (xoffset), m_Yoffset (yoffset){}

		inline float GetXoffset() const { return m_Xoffset; }
		inline float GetYoffset() const { return m_Yoffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScroll:  " << "x: " << m_Xoffset << "y: " << m_Yoffset;
			return ss.str();
		}


		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_Xoffset, m_Yoffset;

	};



   // mouse Press & release
	class RULOMI_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
			//������ protected class �����޷���������һ���������obj ֻ�ܴ����������Ӵ���
	protected:
		MouseButtonEvent(int button)
			:m_Button(button){}
		int m_Button;
	};

	class RULOMI_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		//��Ӵ���
		MouseButtonPressedEvent(int button)
			:MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent:  " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	//ͬ��
	class RULOMI_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		//��Ӵ���
		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent:  " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};



}


