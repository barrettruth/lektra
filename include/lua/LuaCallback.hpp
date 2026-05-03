#pragma once

#include <functional>

template <typename T> struct LuaCallback
{
    int ref;
    std::function<void(T *)> invoker;
    bool is_once = false;
};
