#pragma once

#include <algorithm>
#include <assert.h>
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

//Unsigned integral types
using u8    = unsigned char;
using u16   = unsigned short;
using u32   = unsigned int;
using u64   = unsigned long long;

//Signed integral types
using i8    = signed char;
using i16   = signed short;
using i32   = signed int;
using i64   = signed long long;

//Floating types
using f32   = float;
using f64   = double;

//Smart Pointer Aliases
template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}