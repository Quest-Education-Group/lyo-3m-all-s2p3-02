#pragma once

#include <iostream>

//template <typename T>
//concept CanRegisterISerializable = requires(T t)
//{
//    { T::Register() } -> std::same_as<std::function<ISerializable*()>>;
//};

template<typename D>
struct AutomaticRegisterProxy
{
public:
    AutomaticRegisterProxy()
    {
        if (!s_registered)
        {
            //ISerializable::s_constructors[typeid(D).name()] = D::Register();
            s_registered = true; // Pour stocker la classe qu'une fois
        }
    };

private:
    static bool s_registered;
};

template <typename T> 
inline bool AutomaticRegisterProxy<T>::s_registered = false;
