//
// Created by Даниил on 11.04.2022.
//

#include "World.h"

#include <utility>

#include "2DFigures/Cube.h"
#include "2DFigures/Circle.h"

#include "ResourceManager.h"

#include "Settings.h"


World::World(const std::string& skyTexturePath,
             const std::string& floorTexturePath) noexcept :
             skyTexture_(*ResourceManager::loadTexture(skyTexturePath))
{
}

Vector World::loadMapFromImage(const std::string& worldPath) noexcept
{
    sf::Image mapImage;
    sf::Color pixel;

    Vector playerPosition = {};

    mapImage.loadFromFile(worldPath);


    for(size_t i = 0; i < CELL_WIDTH; i++)
    {
        for(size_t j = 0; j < CELL_HEIGHT; j++)
        {
            if((i == 1 && j == 1) || (i == 1 && j == CELL_HEIGHT-1) || (i == CELL_HEIGHT-1 && j == 1) || (i ==
            CELL_HEIGHT-1 && j == CELL_HEIGHT-1))
            {
                Circle circle(std::to_string(i + 1) + " " + std::to_string(j + 1) + "-Circle",
                              *ResourceManager::loadTexture(std::string(DATA_DIR + std::string("/texture/woodWall1"
                                                                                               ".jpg"))),
                              {static_cast<float>(i),static_cast<float>(j)});
                objects_.insert({circle.getName(),circle});
            }

            pixel = mapImage.getPixel(i,j);

            if(pixel == sf::Color(0,0,0))
            {
                Cube cube(std::to_string(i + 1) + " " + std::to_string(j + 1) + "-Cube",
                          *ResourceManager::loadTexture(std::string(DATA_DIR + std::string("/texture/wall2.png"))),
                          {static_cast<float>(i), static_cast<float>(j)});
                objects_.insert({cube.getName(),cube});
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
    objects_.insert({object2D.getName(), object2D});
}

void World::draw(sf::RenderTarget& window) const
{
    for(auto obj : objects_)
        obj.second.draw(window);
}

std::map<std::string ,Object2D> &World::getObjects()
{
    return objects_;
}

sf::Texture &World::getSkyTexture()
{
    return skyTexture_;
}

sf::Texture &World::getFloorTexture()
{
    return floorTexture_;
}
