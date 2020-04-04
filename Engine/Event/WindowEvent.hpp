#ifndef ENGINE_WINDOW_EVENT_HPP
#define ENGINE_WINDOW_EVENT_HPP

#include "Event.hpp"
#include <sstream>

namespace Engine
{
	class WindowResizeEvent : public Event
	{
	private:
		unsigned int m_Width;
		unsigned int m_Height;

	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) 
		{
			
		}

		inline unsigned int GetWidth()  const { return m_Width;  }
		inline unsigned int GetHeight() const { return m_Height; }


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		static  EventType GetStaticType(){ return EventType::WindowResize; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowResize"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }

	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		static  EventType GetStaticType(){ return EventType::WindowClose; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowClose"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

}



#endif 
