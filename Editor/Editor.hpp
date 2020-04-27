#pragma once
#include <memory>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Widget.hpp"

namespace RE
{
	class Renderer;
}


class Editor
{
public:
	Editor() = default;
	~Editor();

	void OnStart(GLFWwindow* window,RE::Renderer* renderer);
	void OnTick();
	void PushRender();
private:
	void Create_Widgets();
	void OnTick_Widgets();

	void BeginMainWindow();
	void EndMainWindow();

	void ImGUIInit();
	void ImGUIClose();
private:
	bool m_EditorBegin{ false };
	GLFWwindow* m_Window;
	RE::Renderer* m_Renderer;

	std::string m_EditorName{ u8"±à¼­Æ÷"};
	std::vector<std::unique_ptr<Widget>> m_Widgets;
};