#pragma once

#include <memory>

template<typename T>
class Singleton 
{
public:
    static T& GetInstance();
    virtual ~Singleton() {};
    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;

protected:
    Singleton() {}
};

template<typename T>
T& Singleton<T>::GetInstance()
{
    static T instance;
    return instance;
}
