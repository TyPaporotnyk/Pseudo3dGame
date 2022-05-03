//
// Created by Даниил on 02.05.2022.
//

#include "Painter.h"

#include <cmath>

#include "Entities/2DFigures/Object2D.h"

#include "../Precompiler.h"

void Core::Painter::drawMap(sf::RenderTarget &window, const World &world)
{
    for(auto obj : world.getObjects())
        obj.second.draw(window, world.getCellScale());
}

void Core::Painter::drawWorld(sf::RenderTarget &window, const Camera &camera, const World &world)
{
    int segmentWidth = std::ceil(RESOURCE_MANAGER.getWindowWidth() / camera.getRaysNum());
    float segmentHeightProj = 10;
    float segmentHeight;
    sf::RectangleShape segment;
    sf::Sprite sprite;

    float d = camera.getRaysNum() / 2*tan(camera.getSight()/2);

    float offset = -10 * (camera.getAngle()+1) % world.getSkyTexture().getSize().x;
    sf::Sprite sky;
    sky.setTexture(world.getSkyTexture());
    sky.setScale(2,2);

    sky.setTextureRect(sf::IntRect(offset,0,world.getSkyTexture().getSize().x,
                                   world.getSkyTexture().getSize().y));
    window.draw(sky);
    sky.setTextureRect(sf::IntRect(offset - RESOURCE_MANAGER.getWindowWidth(),0,
                                   world.getSkyTexture().getSize().x,world.getSkyTexture().getSize().y));
    window.draw(sky);
    sky.setTextureRect(sf::IntRect(offset + RESOURCE_MANAGER.getWindowWidth(),0,
                                   world.getSkyTexture().getSize().x,world.getSkyTexture().getSize().y));
    window.draw(sky);

    sf::RectangleShape floor;
    floor.setSize({static_cast<float>(RESOURCE_MANAGER.getWindowWidth()),
                   static_cast<float>(RESOURCE_MANAGER.getWindowHeight())/2});
    floor.setPosition(0,(RESOURCE_MANAGER.getWindowHeight()/2));
    floor.setFillColor(sf::Color(162,101,62));

    window.draw(floor);

    enum Entities entity = Entities::NONE;

    int i = 0;
    for(auto& wall : camera.getCollisionPoints())
    {
        if(wall.first == "")
        {
            i++;
            continue;
        }

        segmentHeight = d * segmentHeightProj / camera.getDepths()[i];
        float wallTextureColumn = 0;

        Vector rayEnd = wall.second;

        if(entity != world.getObjects().find(wall.first)->second.getType())
        {
            sprite.setTexture(world.getObjects().find(wall.first)->second.getWallTexture());
            entity = world.getObjects().find(wall.first)->second.getType();
        }

        if (abs(rayEnd.x - round(rayEnd.x)) < abs(rayEnd.y - round(rayEnd.y)))
        {
            wallTextureColumn = rayEnd.y - std::ceil(rayEnd.y);
        }
        else
        {
            wallTextureColumn = rayEnd.x - std::floorf(rayEnd.x);
        }

        sprite.setTextureRect(sf::IntRect((sprite.getTexture()->getSize().x-1) * wallTextureColumn,
                                          0,RESOURCE_MANAGER.getWindowWidth()/camera.getRaysNum(), sprite.getTexture()->getSize
                        ().y-1));
        sprite.setScale(1,segmentHeight/sprite.getTexture()->getSize().y);
        sprite.setPosition(i*segmentWidth, RESOURCE_MANAGER.getWindowHeight()/2 - segmentHeight/2);

        window.draw(sprite);
        i++;
    }
}


void Core::Painter::drawSight(sf::RenderTarget &window, const Camera &camera, const World &world)
{
    sf::CircleShape circle(world.getCellScale()/3);
    circle.setPosition(camera.getPosition().x * world.getCellScale(), camera.getPosition().y * world.getCellScale());
    circle.setOutlineThickness(2);
    circle.setFillColor(sf::Color(255, 100, 196));
    circle.setOutlineColor(sf::Color(252, 248, 243));

    sf::ConvexShape triangle;
    triangle.setPointCount(camera.getCollisionPoints().size()+2);
    triangle.setPoint(0, {(camera.getPosition().x * world.getCellScale() + world.getCellScale()/3),
                          (camera.getPosition().y * world.getCellScale() + world.getCellScale()/3)});

    for(int i = 0; i < camera.getCollisionPoints().size(); i++)
    {
        triangle.setPoint(i+1, {camera.getCollisionPoints()[i].second.x * world.getCellScale(),
                                camera.getCollisionPoints()[i].second.y * world.getCellScale()});
    }
    triangle.setPoint(camera.getCollisionPoints().size()+1,
                      {(camera.getPosition().x * world.getCellScale() + world.getCellScale()/3),
                       (camera.getPosition().y * world.getCellScale() + world.getCellScale()/3)});

    triangle.setFillColor(sf::Color(0,0,0,0));
    triangle.setOutlineColor(sf::Color::White);
    triangle.setOutlineThickness(3);

    window.draw(triangle);
    window.draw(circle);
}
