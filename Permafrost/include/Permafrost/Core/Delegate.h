#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <map>
#include <tuple>


using FunctionID = std::tuple<uint64_t, uint64_t>;

#define TYPENAME_0_ARG
#define TYPENAME_1_ARG  TYPENAME_0_ARG    typename T1
#define TYPENAME_2_ARG  TYPENAME_1_ARG  , typename T2

#define PROTOTYPE_0_ARG
#define PROTOTYPE_1_ARG PROTOTYPE_0_ARG   T1 Arg1
#define PROTOTYPE_2_ARG PROTOTYPE_1_ARG , T2 Arg2

#define ARGUMENTS_0_ARG
#define ARGUMENTS_1_ARG ARGUMENTS_0_ARG Arg1
#define ARGUMENTS_2_ARG ARGUMENTS_1_ARG Arg2

template<typename... Args>
class Callback { public: virtual void Call(Args... Arguments) = 0; };

template<class TClass, typename... Args>
struct Functor : public Callback<Args...>
{
    void Call(Args... Arguments) override { (Instance->*Method)(Arguments...); }

    Functor(TClass* Instance, void(TClass::* Method)(Args...))
    : Instance(Instance)
    , Method(Method)
    {}

private:
    TClass* Instance;
    void(TClass::* Method)(Args...);
};

/*
struct Delegate0
{
    template<class TClass>
    void Bind(TClass* Instance, void (TClass::*Method) ( PROTOTYPE_0_ARG ))
    {
        FunctionID ID( (uint64_t) &Instance, (uint64_t) &Method );
        auto Pointer = std::bind(Method, Instance, std::placeholders::_1);
        Callbacks.insert({ ID,  Pointer });
    }

    void Bind(void (*FunctionPtr) ( PROTOTYPE_0_ARG ))
    {
        FunctionID              ID      = FunctionID(0, reinterpret_cast<uint64_t>(FunctionPtr));
        std::function<void( PROTOTYPE_0_ARG )> Pointer(Function);
        Callbacks.insert({ ID, Pointer });
    }

    void Broadcast() const
    {
        for (auto& Pair : Callbacks)
        {
            Pair.second();
        }
    }

private:
    std::map<FunctionID, std::function<void()>> Callbacks;
};
//*/

/*
template<typename ... Args>
struct Delegate
{
    using FSignature    = std::tuple<uint64_t, uint64_t>;

    template<class TClass>
    using TMethodPtr    = void(TClass::*)(Args...);
    using TFunctionPtr  = void(*)(Args...);

    /// Bind Method to Delegate
    template<class TClass>
    void Bind(TClass* Instance, TMethodPtr<TClass> MethodPtr)
    {
        FSignature Signature    = { (uint64_t) &Instance, (uint64_t) &MethodPtr };
        std::function<void(Args...)> Callback = std::bind(MethodPtr, Instance, std::placeholders::_1);
        Callbacks.insert({ Signature, Callback });
    }

    /// Unbind Method from Delegate
    template<class TClass>
    void Unbind(TClass* Instance, TMethodPtr<TClass> MethodPtr)
    {
        FSignature Signature    = { (uint64_t) &Instance, (uint64_t) &MethodPtr };
        Callbacks.erase(Signature);
    }

    /// Bind Function to Delegate
    void Bind(TFunctionPtr FunctionPtr)
    {
        FSignature Signature    = { 0, (uint64_t) &FunctionPtr };
        std::function<void(Args...)> Callback = &FunctionPtr;
        Callbacks.insert({ Signature, Callback });
    }

    /// Unbind Function from Delegate
    void Unbind(TFunctionPtr FunctionPtr)
    {
        FSignature Signature    = { 0, (uint64_t) &FunctionPtr };
        Callbacks.erase(Signature);
    }

    void Broadcast(Args ... Arguments) const
    {
        for (auto& Pair : Callbacks)
        {
            Pair.second(Arguments...);
        }
    }

    Delegate() = default;
private:
    //Delegate(const Delegate&) = delete;
    //Delegate& operator=(const Delegate&) = delete;

    std::map<FSignature, std::function<void(Args...)>> Callbacks;
};

//*/