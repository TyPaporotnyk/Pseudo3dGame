//
// Created by Даниил on 11.04.2022.
//

#include "World.h"

#include <utility>

#include "../Core/ResourceManager.h"

World::World(const std::string& skyTexturePath,
             const std::string& floorTexturePath, int cellScale) noexcept :
             skyTexture_(*ResourceManager::loadTexture(skyTexturePath)),
//             floorTexture_(*ResourceManager::loadTexture(floorTexturePath)),
             cellScale_(cellScale){ }

void World::addObject(const Object2D& object2D) noexcept
{
    objects_.insert({object2D.getName(), object2D});
}

void World::drawMap(sf::RenderTarget& window) const noexcept
{
    for(auto obj : objects_)
        obj.second.draw(window, cellScale_);
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

int World::getCellScale() const
{
    return cellScale_;
}
