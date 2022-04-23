//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_IDRAWBLE_H
#define PSEUDO3DGAME_IDRAWBLE_H

#include <SFML/Graphics.hpp>

class IDrawable
{
    virtual void draw(sf::RenderTarget &window) = 0;
};

#endif //PSEUDO3DGAME_IDRAWBLE_H
