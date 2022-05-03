//
// Created by Даниил on 11.04.2022.
//

#include "World.h"

#include <utility>

#include "../../Precompiler.h"

World::World(const std::string& skyTexturePath,
             const std::string& floorTexturePath, int cellScale) noexcept :
             skyTexture_(*RESOURCE_MANAGER.loadTexture(skyTexturePath)),
//             floorTexture_(*ResourceManager::loadTexture(floorTexturePath)),
             cellScale_(cellScale) {}

void World::drawMap(sf::RenderTarget& window) const noexcept
{

}

const std::map<std::string ,Object2D> &World::getObjects() const
{
    return objects_;
}

const sf::Texture &World::getSkyTexture() const
{
    return skyTexture_;
}

const sf::Texture &World::getFloorTexture() const
{
    return floorTexture_;
}

int World::getCellScale() const
{
    return cellScale_;
}

void World::addObject(const Object2D &object2D)
{
    objects_.insert({object2D.getName(), object2D});
}
