#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "ext/imgui_impl_glfw.h"
#include "ext/imgui_impl_opengl3.h"

#include "Engine.hpp"
#include <iostream>
#include <cstdlib>

int main() 
{
	if (!glfwInit())
				return 1;
	const char *glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui - Conan", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
	bool err = glewInit() != GLEW_OK;
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
			return 1;
	}

	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	srand(0);
	bool active = true;
	MSQ::Engine e(192000, 512);

	std::vector<const PaDeviceInfo*> devices = e.getDevices();

	for(int i = 0; i < devices.size(); i++) 
	{
		std::cout << i << ": " << MSQ::Engine::deviceInfoToString(devices[i]);
	}

	e.setOutputParameters(22,2);
	e.start();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.f, 0.f, 0.f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Parent", &active, ImGuiWindowFlags_MenuBar);
		e.mainPipeline->render();
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
