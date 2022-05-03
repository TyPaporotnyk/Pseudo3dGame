//
// Created by Даниил on 02.05.2022.
//

#ifndef PSEUDO3DGAME_WORLDLOADER_H
#define PSEUDO3DGAME_WORLDLOADER_H

#include "../World.h"

class World;

namespace Loaders
{
    class WorldLoader
    {
    public:
        void loadMap(World &world, const std::string &path);

    };
}


#endif //PSEUDO3DGAME_WORLDLOADER_H
