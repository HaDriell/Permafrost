#include <Permafrost/Core/Application.h>
#include <Permafrost/Core/Delegate.h>
#include <Permafrost/Core/Log.h>

#include <Permafrost/Core/ActionMap.h>
#include <Permafrost/Graphics/Window.h>
#include <Permafrost/Graphics/GraphicsModule.h>

#include <iostream>

void Initialize(int argc, char* argv[])
{
	ActionMap Actions;
	Actions.Add("Test");
	Actions.GetAction("Test")->Activate();
}

void Main()
{
	std::shared_ptr<Window> Window;
	GraphicsModule::Get()->Open(Window);
	std::cin.get();
}