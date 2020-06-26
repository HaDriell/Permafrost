#include <Permafrost/Core/Application.h>
#include <Permafrost/Core/Delegate.h>
#include <Permafrost/Core/Log.h>
#include <Permafrost/Graphics/Renderer.h>
#include <Permafrost/Graphics/Window.h>
#include <Permafrost/Graphics/WindowEventLoop.h>
#include <Permafrost/Core/Reflection/Reflection.h>

#include <glad/glad.h>
#include <memory>

class Base { REFLECT(Base); };
class Child : public Base { REFLECT(Child); };

REFLECT_IMPL(Base);
REFLECT_IMPL_CHILD(Child, Base);






static std::unique_ptr<Renderer> s_Renderer;

void Initialize(int argc, char* argv[])
{
	spdlog::set_level(spdlog::level::level_enum::debug);
}

void OnWindowRender()
{
	//Clear Frame
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Lazy Initialization
	if (!s_Renderer)
	{
		s_Renderer.reset(new Renderer());
	}

	s_Renderer->Begin();

	s_Renderer->DrawRect(0, 0, 10, 10);

	s_Renderer->End();
}

void Main()
{
	auto MyWindow = Window::Open(); 
	MyWindow->OnRender.Bind(&OnWindowRender);
	
    WindowEventLoop::Get().ExecuteMainLoop();
}