#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"
#include "Permafrost/Core/Delegate.h"

class Input
{
public:
    Delegate<KeyCode> OnKeyPressed;
    Delegate<KeyCode> OnKeyReleased;
    
    Delegate<MouseCode> OnButtonPressed;
    Delegate<MouseCode> OnButtonReleased;

    bool IsKeyPressed(KeyCode code);
    bool IsMousePressed(MouseCode code);
};