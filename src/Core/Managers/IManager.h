//
// Created by Даниил on 02.05.2022.
//

#ifndef PSEUDO3DGAME_IMANAGER_H
#define PSEUDO3DGAME_IMANAGER_H


namespace Core::Managers
{
    template<class T>
    struct IManager
    {
        void initialize();
    };

    template <class T>
    void IManager<T>::initialize()
    {
        static_cast<T*>(this)->initialize();
    }
};


#endif //PSEUDO3DGAME_IMANAGER_H
