#include <Permafrost/Core/Application.h>
#include <Permafrost/Core/CommonTypes.h>
#include <Permafrost/Core/Configuration.h>
#include <Permafrost/Core/Delegate.h>
#include <Permafrost/Core/Log.h>
#include <Permafrost/Graphics/Renderer.h>
#include <Permafrost/Graphics/RenderUtil.h>
#include <Permafrost/Graphics/Window.h>
#include <Permafrost/Graphics/WindowEventLoop.h>
#include <Permafrost/Core/Reflection/Reflection.h>

void Configure(int argc, char** argv)
{
	LOG_INFO("ARG[0] = {0}", argv[0]);
	spdlog::set_level(spdlog::level::level_enum::debug);

	if (!Configuration::Get()->Load("Permafrost.properties"))
	{
		LOG_WARNING("'Permafrost.properties' file not present or invalid !");
		Configuration::Get()->Save("Permafrost.properties");
	}
	
	if (!Configuration::Get()->Parse(argc, argv))
	{
		LOG_CRITICAL("Invalid input parameters, aborting Permafrost.");
		std::exit(1);
	}
}

void OnWindowRender()
{
	//Clear Frame
	RenderUtil::SetClearColor(0, 0, 0, 1);
	RenderUtil::Clear();

	RenderUtil::Get()->Begin(glm::mat4(1));
	RenderUtil::Get()->DrawRect(-0.5f, -0.5f, 1, 1);
	RenderUtil::Get()->End();
}

void Main()
{
	auto MyWindow = Window::Open();
	MyWindow->OnRender.Bind(&OnWindowRender);

    WindowEventLoop::Get().ExecuteMainLoop();
}