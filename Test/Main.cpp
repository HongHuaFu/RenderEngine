#include <Engine.hpp>
#include <Core/EntryPoint.hpp>

namespace Engine
{
	class Sandbox : public Application
	{
	public:
		virtual void EventWindowResize(WindowResizeEvent& e) override
		{
			LOG_INFO("Window resize ({0},{1})",e.GetWidth(),e.GetHeight());
		}

	};
	
	Application* CreateApplication()
	{
		return new Sandbox();
	}
}





