//
// Created by Даниил on 02.05.2022.
//

#ifndef PSEUDO3DGAME_SINGLETON_H
#define PSEUDO3DGAME_SINGLETON_H


namespace Helper::Holders
{

    template<class T>
    class Singleton
    {
    protected:
        Singleton() noexcept = default;

    public:
        static T& getInstance() noexcept;
        explicit Singleton(const Singleton& other) = delete;
        Singleton& operator = (const Singleton& other) = delete;
    };

    template<class T>
    T& Singleton<T>::getInstance() noexcept
    {
        static T instance{};
        return instance;
    }

}


#endif //PSEUDO3DGAME_SINGLETON_H
