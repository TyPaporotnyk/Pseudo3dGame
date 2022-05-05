//
// Created by Даниил on 25.04.2022.
//

#include "Circle.h"

#include <cmath>

Circle::Circle(std::string name, sf::Texture& wallTexture, Vector position, float radius) :
        Object2D(std::move(name), wallTexture, Entities::CIRCLE, position), _radius(radius)
{
    float p = 10;
    for(float i = 0; i < 360; i+=p)
    {
        float a = radius * cosf(i * M_PI / 180) + position.x;
        float b = radius * sinf(i * M_PI / 180) + position.y;

        _points.emplace_back(a,b);
    }
}

void Circle::draw(sf::RenderTarget &window) const
{

}
