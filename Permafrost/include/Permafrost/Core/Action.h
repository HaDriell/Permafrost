#pragma once

#include "Permafrost/Core/Delegate.h"


class Action
{
public:
    Action() : Activated(false) {}

    void Activate();
    void Deactivate();


    //Action Events
    Delegate<> OnActionActivated;
    Delegate<> OnActionDeactivated;

private:
    bool Activated;
};