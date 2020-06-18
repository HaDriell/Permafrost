#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <vector>

template<typename TPointer>
std::uintptr_t GetPointerAddress(TPointer Ptr)
{
	std::uintptr_t* AddressPtr = reinterpret_cast<std::uintptr_t*>(&Ptr);
	return *AddressPtr;
}

template<typename... Args>
class Callback
{
public:
	virtual void Call(Args... Arguments) = 0;
	virtual bool IsTargetting(std::uintptr_t InstanceAddress, std::uintptr_t FunctionAddress) const = 0;
};

template<class TClass, typename... Args>
struct MethodCallback : public Callback<Args...>
{
	void Call(Args... Arguments) override { (Instance->*Method)(Arguments...); }
	bool IsTargetting(std::uintptr_t InstanceAddress, std::uintptr_t FunctionAddress) const override
	{
		return InstanceAddress == GetPointerAddress(Instance)
			&& FunctionAddress == GetPointerAddress(Method);
	}

	MethodCallback(TClass* Instance, void(TClass::* Method)(Args...))
		: Instance(Instance)
		, Method(Method)
    {}

private:
    TClass* Instance;
    void(TClass::* Method)(Args...);
};

template<typename... Args>
struct FunctionCallback : public Callback<Args...>
{
	void Call(Args... Arguments) override { (*Function)(Arguments...); }
	bool IsTargetting(std::uintptr_t InstanceAddress, std::uintptr_t FunctionAddress) const override
	{
		return InstanceAddress == 0 
			&& FunctionAddress == GetPointerAddress(Function);
	}

	FunctionCallback(void(*Function)(Args...))
		: Function(Function)
	{}

private:
	void (*Function)(Args...);
};

template<typename... Args>
struct Delegate
{
	using CallbackImpl = Callback<Args...>;
	template<class TClass>
	using MethodCallbackImpl = MethodCallback<TClass, Args...>;
	using FunctionCallbackImpl = FunctionCallback<Args...>;
	

    /// Bind Method to Delegate
    template<class TClass>
    void Bind(TClass* Instance, void (TClass::* Method)(Args...))
    {
        Callbacks.push_back(new MethodCallbackImpl<TClass>(Instance, Method));
    }

    /// Unbind Method from Delegate
    template<class TClass>
    void Unbind(TClass* Instance, void (TClass::*Method)(Args...))
    {
		UnbindInternal(GetPointerAddress(Instance), GetPointerAddress(Method));
    }

    /// Bind Function to Delegate
    void Bind(void(*Function)(Args...))
    {
		Callbacks.push_back(new FunctionCallbackImpl(Function));
    }

    /// Unbind Function from Delegate
    void Unbind(void(*Function)(Args...))
    {
		UnbindInternal(0, GetPointerAddress(Function));
    }


    void Broadcast(Args... Arguments) const
    {
        for (auto& Pair : Callbacks)
        {
			Pair->Call(Arguments...);
        }
    }
private:
	void UnbindInternal(std::uintptr_t InstanceAddress, std::uintptr_t FunctionAddress)
	{
		for (auto It = Callbacks.begin(); It != Callbacks.end(); ++It)
		{
			if ((*It)->IsTargetting(InstanceAddress, FunctionAddress))
			{
				Callbacks.erase(It);
				break;
			}
		}
		return;
	}

private:
	std::vector<CallbackImpl*> Callbacks;
};