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

void DrawRedFrame()
{
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void DrawBlackFrame()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Main()
{
	auto Red = Window::Open(); 
	Red->OnRender.Bind(&DrawRedFrame);

	auto Black = Window::Open();
	Black->OnRender.Bind(&DrawBlackFrame);	
	
    WindowEventLoop::Get().ExecuteMainLoop();
}