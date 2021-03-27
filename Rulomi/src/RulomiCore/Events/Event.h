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


	//这里用 bit表示的话每个种类 只占用一位 可以mask xor？这种按位操作
	//这个地方就不是class wtf？ 这俩有区别么
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

	//这个具体操作我确实不知
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

	//friend class 可以访问 protected & private
	class RULOMI_API Event
	{
		//friend class EventDispatcher;
	public:
		bool Handled = false;

		//获取具体类型和  大类
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual const char* GetName() const = 0;
		//  std::string有一个 = 被重写了从而将 const char* 类型赋值 std::strings
		//  这个就是 一般虚函数（即有预先设定好的 定义） 子类如果不想用这个，他就得加上 override来重写。
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	};

	//event处理器(每个事件一个？) 由这个类将监听到的事件传递出去
	class EventDispatcher {
		//EventFn 是处理对应Eventtype的函数  T 是任何一种EventType  
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event)
		{

		}

		//Dispatch 自身是一个模板函数 需要指定类型，但
		// func 是处理此类event的函数，并且返回值是 bool
		//参数 func指向 ’处理函数‘
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			//  这个地方的T 是对应 ‘处理函数(event的引用)' 的类型 
			if (m_Event.GetEventType() == T::GetStaticType() ) 
			{
				//取出这个event 的地址（指针） 将他向下转型到精确的event类型（任然是指针）
				//最后解指针 拿到reference
				//因为在上面的if 已经判断过这个地方能否转型
				// 之后 将event 传递给这个处理函数（func） 让他启动做处理
				m_Event.Handled = func(*(T*)&m_Event);
					return true;
			}
			return false;
		}

	private:
		//这个是个引用 声明
		Event& m_Event;

	};


	//重载一个 << 为Log系统服务  Log  这是一个非成员函数 (没有默认对象this, 所以要给出)
	inline std::ostream& operator << (std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}

