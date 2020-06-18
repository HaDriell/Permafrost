#pragma once

#include <memory>

template<class T>
class Module
{
    friend T;
    Module() = default;
    ~Module() = default;
    Module(const Module&) = delete;
    Module& operator=(const Module&) = delete;

public:
    static std::unique_ptr<T>& Get();
};

/// Get (Lazy instanciation) the Required Module
template<typename T>
std::unique_ptr<T>& Module<T>::Get()
{
    static std::unique_ptr<T> ModuleInstance(new T());
    return ModuleInstance;
}