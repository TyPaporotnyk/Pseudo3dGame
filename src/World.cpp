//
// Created by Даниил on 11.04.2022.
//

#include "World.h"

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
