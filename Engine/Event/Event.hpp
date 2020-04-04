#ifndef ENGINE_EVENT_HPP
#define ENGINE_EVENT_HPP

#include <string>

namespace Engine
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = 1 << 0
	};

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


	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// 类外重载，输出事件类别
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}

#endif 
