//
// Created by Даниил on 02.05.2022.
//

#include "Painter.h"

#include <cmath>

#include "Entities/2DFigures/Object2D.h"

void Core::Painter::drawMap(sf::RenderTarget &window, const World &world)
{
    for (auto obj: world.getObjects())
        obj.second->draw(window, world.getCellScale());
}

void Core::Painter::drawWorld(sf::RenderTarget &window, const Camera &camera, const World &world, bool texturing)
{
    sf::RectangleShape segment;
    sf::Sprite sprite;

    float offset = -10 * (camera.getAngle() + 1) % world.getSkyTexture().getSize().x;
    sf::Sprite sky;
    sky.setTexture(world.getSkyTexture());
    sky.setScale(2, 2);

    sky.setTextureRect(sf::IntRect(offset, 0, world.getSkyTexture().getSize().x,
                                   world.getSkyTexture().getSize().y));
    window.draw(sky);
    sky.setTextureRect(sf::IntRect(offset - world.getWindowWidth(), 0,
                                   world.getSkyTexture().getSize().x, world.getSkyTexture().getSize().y));
    window.draw(sky);
    sky.setTextureRect(sf::IntRect(offset + world.getWindowWidth(), 0,
                                   world.getSkyTexture().getSize().x, world.getSkyTexture().getSize().y));
    window.draw(sky);

    sf::RectangleShape floor;
    floor.setSize({static_cast<float>(world.getWindowWidth()),
                   static_cast<float>(world.getWindowHeight()) / 2});
    floor.setPosition(0, world.getWindowHeight() / 2);
    floor.setFillColor(sf::Color(162, 101, 62));

    window.draw(floor);

    enum Entities entity = Entities::NONE;

    std::vector<Point> collisions = camera.getCollisionPoints();
    std::sort(collisions.begin(), collisions.end(),
              [](const Point &a, const Point &b) -> bool {
                  return a.depth > b.depth;
    });

    for (auto &wall: collisions)
    {
        if (wall.name == "")
            continue;


        if (entity != world.getObjects().find(wall.name)->second->getType())
        {
            sprite.setTexture(world.getObjects().find(wall.name)->second->getWallTexture());
            entity = world.getObjects().find(wall.name)->second->getType();
        }

        Vector rayEnd = wall.position;
        float wallTextureColumn = 0;
        if (abs(rayEnd.x - roundf(rayEnd.x)) < abs(rayEnd.y - roundf(rayEnd.y)))
        {
            wallTextureColumn = rayEnd.y - std::ceilf(rayEnd.y);
        } else
        {
            wallTextureColumn = rayEnd.x - std::floorf(rayEnd.x);
        }

        float segmentHeight = camera.getRaysNum() * tan(camera.getSight()) / wall.depth;
        float segmentWidth = std::ceil(world.getWindowWidth() / camera.getRaysNum());
        if (texturing)
        {
            sprite.setTextureRect(sf::IntRect((sprite.getTexture()->getSize().x) * wallTextureColumn,
                                              0, world.getWindowWidth() / camera.getRaysNum(),
                                              sprite.getTexture()->getSize().y));
            sprite.setColor(sf::Color(255 - 100 / camera.getMaxDist() * wall.depth,
                                      255 - 100 / camera.getMaxDist() * wall.depth,
                                      255 - 100 / camera.getMaxDist() * wall.depth));
            sprite.setScale(1, segmentHeight / sprite.getTexture()->getSize().y);
            sprite.setPosition(wall.rayNum * segmentWidth, world.getWindowHeight() / 2 - segmentHeight / 2);

            window.draw(sprite);
        } else
        {
            sf::RectangleShape rectangle;
            rectangle.setSize({static_cast<float>(segmentWidth), static_cast<float>(segmentHeight)});
            rectangle.setPosition(wall.rayNum * segmentWidth, world.getWindowHeight() / 2 - segmentHeight / 2);
            rectangle.setFillColor(sf::Color(50 - 50 / camera.getMaxDist() * wall.depth,
                                             181 - 181 / camera.getMaxDist() * wall.depth,
                                             217 - 217 / camera.getMaxDist() * wall.depth));
            window.draw(rectangle);
        }
    }
}


void Core::Painter::drawSight(sf::RenderTarget &window, const Camera &camera, const World &world)
{
    sf::RectangleShape field;
    field.setSize({static_cast<float>(20 * world.getCellScale()), static_cast<float>(20 * world.getCellScale())});
    field.setFillColor(sf::Color(162, 101, 62));

    sf::CircleShape circle(world.getCellScale() / 3);
    circle.setPosition(camera.getPosition().x * world.getCellScale(), camera.getPosition().y * world.getCellScale());
    circle.setOutlineThickness(2);
    circle.setFillColor(sf::Color(255, 100, 196));
    circle.setOutlineColor(sf::Color(252, 248, 243));

    sf::Vertex ray[] = {
            sf::Vertex({(camera.getPosition().x * world.getCellScale() + world.getCellScale() / 3),
                        (camera.getPosition().y * world.getCellScale() + world.getCellScale() / 3)}),
            sf::Vertex({static_cast<float>((camera.getPosition().x * world.getCellScale() + world.getCellScale() / 3) +
                                           cos((360 - camera.getAngle()) * M_PI / 180) * world.getCellScale()),
                        static_cast<float>((camera.getPosition().y * world.getCellScale() + world.getCellScale() / 3) +
                                           sin((360 - camera.getAngle()) * M_PI / 180) * world.getCellScale())})
    };

    ray[0].color = sf::Color(0, 255, 0);
    ray[1].color = sf::Color(0, 255, 0);

    sf::ConvexShape triangle;

    int size = camera.getCollisionPoints().size() / (camera.getCollisionPoints().size() / 100);

    triangle.setPointCount(size + 2);
    triangle.setPoint(0, {(camera.getPosition().x * world.getCellScale() + world.getCellScale() / 3),
                          (camera.getPosition().y * world.getCellScale() + world.getCellScale() / 3)});

    int j = 0;
    for (int i = 0; i < camera.getCollisionPoints().size(); i += camera.getCollisionPoints().size() / 100)
    {
        triangle.setPoint(j + 1, {camera.getCollisionPoints()[i].position.x * world.getCellScale(),
                                  camera.getCollisionPoints()[i].position.y * world.getCellScale()});
        j++;
    }
    triangle.setPoint(size + 1,
                      {(camera.getPosition().x * world.getCellScale() + world.getCellScale() / 3),
                       (camera.getPosition().y * world.getCellScale() + world.getCellScale() / 3)});

    triangle.setFillColor(sf::Color(0, 0, 0, 0));
    triangle.setOutlineColor(sf::Color::White);
    triangle.setOutlineThickness(3);

    window.draw(field);
    window.draw(triangle);
    window.draw(ray, 2, sf::LinesStrip);
    window.draw(circle);
}
