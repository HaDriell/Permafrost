#include <Permafrost/Core/Application.h>
#include <Permafrost/Core/Delegate.h>
#include <Permafrost/Core/Log.h>

#include <vector>

class A
{
public:
    void AMethod() { LOG_INFO("A::AMethod Called"); }
	void BMethod() { LOG_INFO("A::BMethod Called"); }
    static void Function() { LOG_INFO("A::Function Called"); }
};

class B
{
public:
	void AMethod() { LOG_INFO("B::AMethod Called"); }
};

void Initialize(int argc, char* argv[])
{
    A a;
	B b;

	Delegate<> OnEvent;
	OnEvent.Bind(&a, &A::AMethod);
	OnEvent.Bind(&a, &A::BMethod);
	OnEvent.Bind(&b, &B::AMethod);
	OnEvent.Bind(&A::Function);

	OnEvent.Broadcast();

	LOG_INFO("*** Unbinding A::Function");
	OnEvent.Unbind(&A::Function);

	OnEvent.Broadcast();

	LOG_INFO("*** Unbinding a->BMethod");
	OnEvent.Unbind(&a, &A::BMethod);

	OnEvent.Broadcast();
}

void Main()
{
}