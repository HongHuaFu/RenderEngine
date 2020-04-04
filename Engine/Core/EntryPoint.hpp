#ifndef ENGINE_ENTRY_POINT_HPP
#define ENGINE_ENTRY_POINT_HPP

#if defined APPLICATION_

extern Engine::Application* Engine::CreateApplication();

int main()
{
	Engine::Log::Init();

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;

	return 0;
}
#endif

#endif // !EntryPoint
