#include <Permafrost/Core/Application.h>
#include <Permafrost/Core/CommonTypes.h>
#include <Permafrost/Core/Configuration.h>
#include <Permafrost/Core/Delegate.h>
#include <Permafrost/Core/Log.h>
#include <Permafrost/Graphics/Renderer.h>
#include <Permafrost/Graphics/RenderUtil.h>
#include <Permafrost/Graphics/Window.h>
#include <Permafrost/Graphics/WindowEventLoop.h>

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
}