//
// Created by Даниил on 11.04.2022.
//

#include "World.h"

#include <utility>

#include "2DFigures/Cube.h"
#include "2DFigures/Circle.h"

#include "Settings.h"


World::World(std::vector<Object2D> objects) noexcept :
objects_(std::move(objects))
{

}

Vector World::loadMapFromImage(std::string& imgPath) noexcept
{
    sf::Image mapImage;
    sf::Color pixel;

    Vector playerPosition = {};

    mapImage.loadFromFile(imgPath);

    for(size_t i = 0; i < CELL_WIDTH; i++)
    {
        for(size_t j = 0; j < CELL_HEIGHT; j++)
        {
            if((i == 1 && j == 1) || (i == 1 && j == CELL_HEIGHT-1) || (i == CELL_HEIGHT-1 && j == 1) || (i ==
            CELL_HEIGHT-1 && j == CELL_HEIGHT-1))
            {
                objects_.push_back(Circle({static_cast<float>(i),static_cast<float>(j)}));
            }

            pixel = mapImage.getPixel(i,j);

            if(pixel == sf::Color(0,0,0))
            {
                objects_.push_back(Cube({static_cast<float>(i),static_cast<float>(j)}));
            }
            else if(pixel == sf::Color(0,0,255))
            {
                playerPosition = {static_cast<float>(i),static_cast<float>(j)};
            }
        }
    }

    return playerPosition;
}

void World::addObject(const Object2D& object2D) noexcept
{
    objects_.push_back(object2D);
}

void World::draw(sf::RenderTarget& window) const
{
    for(auto& obj : objects_)
        obj.draw(window);
}

std::vector<Object2D> &World::getObjects()
{
    return objects_;
}
