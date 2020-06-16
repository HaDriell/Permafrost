#include <Permafrost/Core/Application.h>
#include <Permafrost/Core/Delegate.h>
#include <Permafrost/Core/Log.h>


class A
{
public:
    void AMethod() { LOG_INFO("Method Called"); }
    static void Function() { LOG_INFO("Function Called"); }
};



void Initialize(int argc, char* argv[])
{
    A object;

    Functor<A> Ftor{ &object, &A::AMethod };
    Ftor.Call();

    // Delegate OnEvent;
    // OnEvent.Bind(&A::Function);
    // OnEvent.Bind(&object, &A::Method);
    // OnEvent.Broadcast();
}

void Main()
{
}