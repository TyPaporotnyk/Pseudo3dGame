//
// Created by Даниил on 24.04.2022.
//

#include "Cube.h"

Cube::Cube(std::string name, sf::Texture& wallTexture, Vector position ,
           const std::vector<Vector>&points, int scale)
: Object2D(std::move(name), wallTexture, Entities::CUBE, position,{{0,0}, {1,0},{1,1},{0,1}}), _scale(scale)
{
    for(auto& v : _points)
    {
        v *= scale;
    }
}

void Cube::draw(sf::RenderTarget &window) const
{

}
