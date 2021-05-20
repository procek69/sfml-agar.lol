#pragma once

template<typename T>
struct deleter : std::unary_function<const T*, void>
{
    void operator() (const T* ptr) const
    {
        delete ptr;
    }
};