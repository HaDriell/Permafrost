#include <Permafrost/Core/Application.h>
#include <Permafrost/Core/Delegate.h>
#include <Permafrost/Core/Log.h>

#include <Permafrost/Core/ActionMap.h>

void Initialize(int argc, char* argv[])
{
	ActionMap Actions;
	Actions.Add("Test");
	Actions.GetAction("Test")->Activate();
}

void Main()
{
}