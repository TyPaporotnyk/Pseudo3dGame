//
// Created by Даниил on 02.05.2022.
//

#ifndef PSEUDO3DGAME_DRAWER_H
#define PSEUDO3DGAME_DRAWER_H

#include "../Helper/Holders/Singleton.h"

#include "Entities/Camera.h"
#include "Entities/World.h"

#include <SFML/Graphics.hpp>

namespace Core
{
    class Drawer// : public Helper::Holders::Singleton<Drawer>
    {
    public:
        static void drawMap(sf::RenderTarget& window, const World& world);

        static void drawWorld(sf::RenderTarget &window, const Camera &camera, const World &world);

        static void drawSight(sf::RenderTarget& window, const Camera& camera, const World& world);
    };
}

#endif //PSEUDO3DGAME_DRAWER_H
