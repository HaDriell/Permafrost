#include "Permafrost/Core/Action.h"
#include "Permafrost/Core/Log.h"

void Action::Activate()
{
    if (!Activated)
    {
        Activated = true;
        OnActionActivated.Broadcast();
    }
}

void Action::Deactivate()
{
    if (Activated)
    {
        Activated = false;
        OnActionDeactivated.Broadcast();
    }
}