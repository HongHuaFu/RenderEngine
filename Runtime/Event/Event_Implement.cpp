#include "Event_Mouse.hpp"
#include "Event_Key.hpp"

namespace RE
{
	bool EventMouseMoved::firstMouse = true;
	float EventMouseMoved::lastX = 640.0f;
	float EventMouseMoved::lastY = 360.0f;

	bool EventKey::keysPressed[1024] = { false };
	bool EventKey::keysActive[1024] = { false };
}