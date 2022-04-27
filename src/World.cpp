//
// Created by Даниил on 11.04.2022.
//

#include "World.h"

#include "2DFigures/Cube.h"
#include "2DFigures/Circle.h"

#include "Settings.h"


World::World(std::vector<Object2D> objects) :
objects(objects)
{

}

void World::draw(sf::RenderTarget& window)
{
    for(auto& obj : objects )
    obj.draw(window);
}

void World::addObject(Object2D object2D)
{
    objects.push_back(object2D);
}

std::vector<Object2D> &World::getObjects()
{
    return objects;
}

Vector World::loadMapFromImage(std::string imgPath)
{
    sf::Image mapImage;
    sf::Color pixel;

    Vector playerPosition;

    mapImage.loadFromFile(imgPath);

    for(size_t i = 0; i < CELL_WIDTH; i++)
    {
        for(size_t j = 0; j < CELL_HEIGHT; j++)
        {
            if((i == 1 && j == 1) || (i == 1 && j == CELL_HEIGHT-1) || (i == CELL_HEIGHT-1 && j == 1) || (i ==
            CELL_HEIGHT-1 && j == CELL_HEIGHT-1))
            {
                objects.push_back(Circle({static_cast<float>(i),static_cast<float>(j)}));
            }

            pixel = mapImage.getPixel(i,j);

            if(pixel == sf::Color(0,0,0))
            {
                objects.push_back(Cube({static_cast<float>(i),static_cast<float>(j)}));
            }
            else if(pixel == sf::Color(0,0,255))
            {
                playerPosition = {static_cast<float>(i),static_cast<float>(j)};
            }
        }
    }

    return playerPosition;
}
