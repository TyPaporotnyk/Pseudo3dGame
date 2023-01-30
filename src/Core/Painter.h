//
// Created by Даниил on 02.05.2022.
//

#ifndef PSEUDO3DGAME_PAINTER_H
#define PSEUDO3DGAME_PAINTER_H

#include "Helper/Holders/Singleton.h"

#include "Entities/Camera.h"
#include "Entities/World.h"

#include <SFML/Graphics.hpp>

namespace Core
{
    struct Painter// : public Helper::Holders::Singleton<Drawer>
    {
        Painter() = delete;
        static void drawMap(sf::RenderTarget& window, const World& world);

        static void drawWorld(sf::RenderTarget &window, const Camera &camera, const World &world, bool texturing =
                false);

        static void drawSight(sf::RenderTarget& window, const Camera& camera, const World& world);
    };
}

#endif //PSEUDO3DGAME_PAINTER_H
