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

    double rotationHorizontal = round(FOV * (windowCenterX - sf::Mouse::getPosition(window).x) / window.getSize().x);

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
        position.x += cosf(degCheck(angle + FOV)*M_PI/180) * speed;
        position.y -= sinf(degCheck(angle + FOV)*M_PI/180) * speed;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        position.x += cosf(degCheck(angle - FOV)*M_PI/180) * speed;
        position.y -= sinf(degCheck(angle - FOV)*M_PI/180) * speed;
    }

    // Crossing rays
    crossing();
}

void Camera::crossing() noexcept
{
    collisionPoints.clear();
    depths.clear();
    for (float a = -FOV/2; a < FOV/2; a++)
    {

//        float ray_direction = angle + FOV * (floor(0.5f * WINDOW_WIDTH) - a) / (WINDOW_WIDTH - 1);
        Vector direction = {cosf((angle - a) * M_PI / 180),
                            -sinf((angle - a) * M_PI / 180)};
        direction.normalize();

        float bestLen = maxDist;
        Vector bestPoint = {(position.x  + direction.x  * bestLen), (position.y + direction.y * bestLen)};

        for(auto& object : world.getObjects())
        {
            for(int i = 0; i < object.getNodes().size(); i++)
            {
                Vector wallPoint1 = object.getNodes()[i % object.getNodes().size()];
                Vector wallPoint2 = object.getNodes()[(i + 1) % object.getNodes().size()];
                Vector rayStart = position;

                Vector rayDir = rayStart + direction;

                double den = (wallPoint1.x - wallPoint2.x) * (rayStart.y - rayDir.y) -
                            (wallPoint1.y - wallPoint2.y) * (rayStart.x - rayDir.x);

                if (den == 0)
                {
//                    collisionPoints.push_back(bestPoint);
                    continue;
                }

                double t = ((wallPoint1.x - rayStart.x) * (rayStart.y - rayDir.y) -
                           (wallPoint1.y - rayStart.y) * (rayStart.x - rayDir.x)) / den;
                double u = -((wallPoint1.x - wallPoint2.x) * (wallPoint1.y - rayStart.y) -
                          (wallPoint1.y - wallPoint2.y) * (wallPoint1.x - rayStart.x)) / den;

                if (t >= 0 && t <= 1 && u >= 0 )
                {
                    if (u < bestLen)
                    {
                        bestPoint = {static_cast<float>(rayStart.x + u * (rayDir.x - rayStart.x)),
                                                   static_cast<float>(rayStart.y + u * (rayDir.y - rayStart.y))};
                        bestLen = u;
                    }
                }
            }
        }
        collisionPoints.push_back(bestPoint);
        depths.push_back(bestLen);
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

    triangle.setFillColor(sf::Color(0,0,0,0));
    triangle.setOutlineColor(sf::Color::White);
    triangle.setOutlineThickness(3);

    window.draw(triangle);
    window.draw(circle);
}

void Camera::drawWorld(sf::RenderTarget &window)
{
    float D = WINDOW_WIDTH / FOV;
    float H = 50;
    float h;

    sf::RectangleShape rec;
    rec.setSize({WINDOW_WIDTH, WINDOW_HEIGHT/2});
    rec.setFillColor(sf::Color(135,206,235));
    window.draw(rec);

    for(int i = 0; i < FOV; i++)
    {
        if(depths[i] >= maxDist) continue;
        h = D * H / depths[i];
        rec.setSize({D, h});
        rec.setPosition(i*D, WINDOW_HEIGHT/2 - h/2);
        rec.setFillColor(sf::Color(255-depths[i]*(255/maxDist),255-depths[i]*(255/maxDist),255-depths[i]*(255/maxDist)));
        window.draw(rec);
    }
}

float Camera::degCheck(float deg)
{
    return static_cast<float>(fmod(360 + fmod(deg, 360), 360));
}
