#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include "ext/imgui_impl_glfw.h"
#include "ext/imgui_impl_opengl3.h"

#include "core/Engine.hpp"
#include "playables/LoopingSampler.hpp"
#include "playables/Amp.hpp"
#include <iostream>
#include <cstdlib>

GLFWwindow *window;

void ErrorCallback(int, const char* err_str)
{
    std::cout << "GLFW Error: " << err_str << std::endl;
}

void uiStart()
{
	glfwSetErrorCallback(ErrorCallback);
	int err = glfwInit();
	if (!err)
		fprintf(stderr, "Failed to initialize GLFW!\n");
	const char *glsl_version = "#version 330";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(1280, 720, "Dear ImGui - Conan", NULL, NULL);
	if (!window)
		fprintf(stderr, "Failed to initialize Window!\n");
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
	err = glewInit();
	if (err != GLEW_OK)
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");

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
}

void uiKill()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}


int main() 
{
	uiStart();
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
	MSQ::Sample sample("sample.flac");
	MSQ::LoopingSampler s({e.getSampleRate(), e.getFramesPerBuffer()}, &sample);
	MSQ::Amp a({e.getSampleRate(), e.getFramesPerBuffer()}, 2);
	e.mainPipeline->insert(0, &s);
	e.mainPipeline->insert(1, &a);

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
	uiKill();
	return 0;
}

