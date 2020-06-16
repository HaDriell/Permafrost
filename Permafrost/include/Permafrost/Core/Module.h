#pragma once

#include <memory>

template<typename T>
class Module
{
    friend T;

    Module() = default;
    ~Module() = default;
    Module(const Module&) = delete;
    Module& operator=(const Module&) = delete;

public:
    static std::unique_ptr<T> Get();

private:
    static std::unique_ptr<T> Instance;
};


/// Get (Lazy instanciation) the Required Module
template<typename T>
std::unique_ptr<T> Module<T>::Get()
{
    if (!Module<T>::Instance)
    {
        Module<T>::Instance.reset(new T());
    }
    return Module<T>::Instance;
}