#pragma once

#include <glm/glm.hpp>

#include "KeyCodes.h"
#include "MouseCodes.h"
#include "Permafrost/Core/Delegate.h"

class UserInput
{
public:
    //Keyboard Input
    Delegate<KeyCode> OnKeyPressed;
    Delegate<KeyCode> OnKeyReleased;

    //Mouse Button Input
    Delegate<MouseCode> OnMouseButtonPressed;
    Delegate<MouseCode> OnMouseButtonReleased;
    
    //Mouse Position Input
    Delegate<glm::vec2> OnMouseMoved;
    Delegate<glm::vec2> OnMouseScrolled;

    //Mouse Hover Input
    Delegate<> OnMouseEnter;
    Delegate<> OnMouseLeave;
};