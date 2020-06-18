#include <Permafrost/Core/ActionMap.h>
#include <Permafrost/Core/Application.h>
#include <Permafrost/Core/Delegate.h>
#include <Permafrost/Core/Log.h>
#include <Permafrost/Graphics/Window.h>
#include <Permafrost/Graphics/WindowEventLoop.h>

#include <glad/glad.h>
#include <iostream>

void Initialize(int argc, char* argv[])
{
	ActionMap Actions;
	Actions.Add("Test");
	Actions.GetAction("Test")->Activate();
}

void Main()
{
	Window window;
	window.Open();

	while(true)
	{
		window.BeginFrame();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		window.EndFrame();
	}
	window.Close();
	WindowEventLoop::Get().Wait();
}