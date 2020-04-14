#pragma once

#include "Event.hpp"
#include <GLFW/glfw3.h>

namespace RE
{
	class EventKey : public Event
	{
	public:
		EventKey(int key,int action) : key(key), action(action) {}

		int GetKey() const { return key; }
		int GetAction() const { return action; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyEvent: " << key << ", " << action;
			return ss.str();
		}

		static  EventType GetStaticType(){ return EventType::Key; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "Key"; }
		virtual int GetCategoryFlags() const override { return EventCategoryApplication; }
	public:
		static bool keysPressed[1024];
		static bool keysActive[1024];

	private:
		int key,action;
	};
}