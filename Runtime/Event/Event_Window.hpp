#pragma once

#include "Event.hpp"
#include <sstream>

namespace RE
{
	class EventWindowResize : public Event
	{
	private:
		unsigned int m_Width;
		unsigned int m_Height;

	public:
		EventWindowResize(unsigned int width, unsigned int height)
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

	class EventWindowClose: public Event
	{
	public:
		EventWindowClose() = default;

		static  EventType GetStaticType(){ return EventType::WindowClose; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowClose"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

}




