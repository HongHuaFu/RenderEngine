#pragma once

#include <string>

namespace RE
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = 1 << 0
	};

	// 事件应仅带必要的信息
	// 主要处理逻辑放在其它类中
	class Event
	{
	public:
		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName()    const = 0;
		virtual int GetCategoryFlags()   const = 0;
		virtual std::string ToString()   const { return GetName(); }

		// 判断是否为该类事件
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	// 在GLFW中绑定各种类型的事件，如：EventWindowClose，EventWindowResize...
	// Application将会设置Window中的事件回调函数 EventCallBackFn(Event&)
	// 详见Application中的事件OnEvent。
	// 每次事件回调发生，EventCallBackFn将根据Event的类别执行对应的函数F。
	// 当然每个F可以设为虚函数，那么子类就可以重载它实现事件重载
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// 函数F类型由编译器推断
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// 若F的参数不满足func参数条件编译器将报错
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// 输出事件类别
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}