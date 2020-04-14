#pragma once

#include "Event.hpp"
#include <sstream>


namespace RE
{
	class EventMouseMoved : public Event
	{
	public:
		EventMouseMoved(float x, float y) : m_MouseX(x), m_MouseY(y) {}

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		static  EventType GetStaticType(){ return EventType::MouseMoved; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseMoved"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	public:
		static bool firstMouse;
		static float lastX;
		static float lastY;

	private:
		float m_MouseX, m_MouseY;
	};

}