//
// Created by Даниил on 11.04.2022.
//

#include "Camera.h"

#include "Settings.h"

#include <cmath>

Camera::Camera(World &world, Vector position, float speed, float angle, float maxDist) :
world(world), position(position), speed(speed), angle(angle), maxDist(maxDist)
{

}

void Camera::control(const sf::RenderWindow& window) noexcept
{
    // Mouse movement
    double windowCenterX = round(window.getSize().x / 2);
    double windowCenterY = round(window.getSize().y / 2);

    double rotationHorizontal = round(90 * (windowCenterX - sf::Mouse::getPosition(window).x) / window.getSize().x);

    angle = degCheck(angle + rotationHorizontal);

    sf::Mouse::setPosition(sf::Vector2i(windowCenterX, windowCenterY), window);

    // Keyboard check
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        position.x += cosf(angle*M_PI/180) * speed;
        position.y -= sinf(angle*M_PI/180) * speed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        position.x -= cosf(angle*M_PI/180) * speed;
        position.y += sinf(angle*M_PI/180) * speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        position.x += cosf(degCheck(angle + 90)*M_PI/180) * speed;
        position.y -= sinf(degCheck(angle + 90)*M_PI/180) * speed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        position.x += cosf(degCheck(angle - 90)*M_PI/180) * speed;
        position.y -= sinf(degCheck(angle - 90)*M_PI/180) * speed;
    }

    // Crossing rays
    crossing();
}

void Camera::crossing() noexcept
{
    collisionPoints.clear();
    for (int a = -45; a < 45; a += 1)
    {
        Vector direction = {cosf(degCheck(angle - a) * M_PI / 180),
                            -sinf(degCheck(angle - a) * M_PI / 180)};
        direction.normalize();

        float bestLen = maxDist;
        Vector bestPoint = {position.x + direction.x * maxDist, position.y + direction.y * maxDist};

        for(auto& object : world.getObjects())
        {
            for(int i = 0; i < object.getNodes().size(); i++)
            {
                Vector wallPoint1 = object.getNodes()[i % object.getNodes().size()];
                Vector wallPoint2 = object.getNodes()[(i + 1) % object.getNodes().size()];
                Vector rayStart = position;

                Vector rayDir = rayStart + direction;

                float den = (wallPoint1.x - wallPoint2.x) * (rayStart.y - rayDir.y) -
                            (wallPoint1.y - wallPoint2.y) * (rayStart.x - rayDir.x);

                if (den == 0)
                {
                    continue;
                }

                float t = ((wallPoint1.x - rayStart.x) * (rayStart.y - rayDir.y) -
                           (wallPoint1.y - rayStart.y) * (rayStart.x - rayDir.x)) / den;
                float u = -((wallPoint1.x - wallPoint2.x) * (wallPoint1.y - rayStart.y) -
                          (wallPoint1.y - wallPoint2.y) * (wallPoint1.x - rayStart.x)) / den;

                if (t > 0 && t < 1 && u > 0)
                {
                    if (u < bestLen)
                    {
                        bestPoint = {rayStart.x + u * (rayDir.x - rayStart.x),
                                                   rayStart.y + u * (rayDir.y - rayStart.y)};
                        bestLen = u;
                    }
                }
            }
        }
        collisionPoints.push_back(bestPoint);
    }
}

void Camera::draw(sf::RenderTarget &window)
{
    sf::CircleShape circle(CELL_SCALE/3);
    circle.setPosition(position.x * CELL_SCALE, position.y * CELL_SCALE);
    circle.setOutlineThickness(2);
    circle.setFillColor(sf::Color(255, 100, 196));
    circle.setOutlineColor(sf::Color(252, 248, 243));

    sf::ConvexShape triangle;
    triangle.setPointCount(collisionPoints.size()+2);
    triangle.setPoint(0, {(position.x * CELL_SCALE + CELL_SCALE/3),
                          (position.y * CELL_SCALE + CELL_SCALE/3)});

    for(int i = 0; i < collisionPoints.size(); i++)
    {
        triangle.setPoint(i+1, {collisionPoints[i].x * CELL_SCALE, collisionPoints[i].y * CELL_SCALE});
    }
    triangle.setPoint(collisionPoints.size()+1, {(position.x * CELL_SCALE + CELL_SCALE/3),
                                                 (position.y * CELL_SCALE + CELL_SCALE/3)});

    triangle.setFillColor(sf::Color::Black);
    triangle.setOutlineColor(sf::Color::White);
    triangle.setOutlineThickness(3);

    window.draw(triangle);
    window.draw(circle);
}

float Camera::degCheck(int deg)
{
    return (360 + (deg % 360))% 360;
}
