//
// Created by Даниил on 24.04.2022.
//

#include "Cube.h"

Cube::Cube(Vector position, int scale)
: Object2D(position, {{0,0},{1,0},
                      {1,1},{0,1}})
{
    for(auto& v : points_)
    {
        v *= scale;
    }
}

void Cube::draw(sf::RenderTarget &window) const
{

}
