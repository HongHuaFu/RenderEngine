#include <Api.hpp>
#include <Core/EntryPoint.hpp>

#include "Editor.hpp"

namespace RE
{
	class Sandbox : public Application
	{
	public:
		virtual void OnStart() override
		{
			m_Editor = new Editor((GLFWwindow*)m_Window->GetNativeWindow());
			m_Editor->OnStart();
		}

		virtual void OnUpdate() override
		{
			m_Editor->OnUpdate();
		}

	private:
		Editor* m_Editor;
	public:
		~Sandbox(){ delete m_Editor; }
	};

	Application* CreateApplication()
	{
		return new Sandbox();
	}
}

