#include <GLFW/glfw3.h>

#include "Permafrost/Core/Delegate.h"
#include "Permafrost/Core/MouseCodes.h"
#include "Permafrost/Core/KeyCodes.h"


struct WindowProperties
{
    
};

class Window
{
public:
    Delegate<> OnRender;


private:
    GLFWwindow* window;
};