//
// Created by Даниил on 11.04.2022.
//

#include "World.h"

#include <utility>

#include "../../Precompiler.h"

World::World(const std::string& skyTexturePath,
             const std::string& floorTexturePath, int cellScale,
             int windowWidth, int windowHeight) noexcept :
             _skyTexture(*RESOURCE_MANAGER.loadTexture(skyTexturePath)),
//             floorTexture_(*ResourceManager::loadTexture(floorTexturePath)),
             cellScale_(cellScale), _windowWidth(windowWidth), _windowHeight(windowHeight)  {}

void World::drawMap(sf::RenderTarget& window) const noexcept
{

}

const std::map<std::string ,Object2D> &World::getObjects() const
{
    return _objects;
}

const sf::Texture &World::getSkyTexture() const
{
    return _skyTexture;
}

const sf::Texture &World::getFloorTexture() const
{
    return _floorTexture;
}

int World::getCellScale() const
{
    return cellScale_;
}

void World::addObject(const Object2D &object2D)
{
    _objects.insert({object2D.getName(), object2D});
}

int World::getWindowWidth() const
{
    return _windowWidth;
}

int World::getWindowHeight() const
{
    return _windowHeight;
}
