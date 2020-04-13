#pragma once

#include <vector>
#include <memory>
#include <GLFW/glfw3.h>

#include "ImGui/imgui.h"

class Editor
{
private:
	GLFWwindow* m_Window;
	ImVec4 m_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
public:
	Editor(GLFWwindow*);
	~Editor();
	void OnStart();
	void OnUpdate();
private:
	void MainWindow_Begin();
	void MainWindow_End();	


};

