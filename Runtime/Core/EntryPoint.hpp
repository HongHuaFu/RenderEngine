#pragma once

#if defined EDITOR_

extern RE::Application* RE::CreateApplication();

int main()
{
	RE::Log::Init();
	auto app = RE::CreateApplication();
	app->Run();
	delete app;

	return 0;
}
#endif
