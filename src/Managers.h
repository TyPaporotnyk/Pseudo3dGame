//
// Created by Даниил on 02.05.2022.
//

#ifndef PSEUDO3DGAME_MANAGERS_H
#define PSEUDO3DGAME_MANAGERS_H

#include "Precompiler.h"

namespace Core::Managers
{

    inline void initialize() noexcept
    {
        RESOURCE_MANAGER.initialize();
    }

}
#endif //PSEUDO3DGAME_MANAGERS_H
