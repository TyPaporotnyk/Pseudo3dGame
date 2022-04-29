//
// Created by Даниил on 11.04.2022.
//

#include "Camera.h"

#include "Settings.h"

#include <iostream>
#include <cmath>

Camera::Camera(World &world, Vector position, float speed, float angle, float maxDist) :
world_(world), position_(position), speed_(speed), angle_(angle), maxDist_(maxDist)
{

}

void Camera::control(const sf::RenderWindow& window, float dTime) noexcept
{
    // Mouse movement
    float windowCenterX = round(window.getSize().x / 2);
    float windowCenterY = round(window.getSize().y / 2);

    float rotationHorizontal = round(90 * (windowCenterX - sf::Mouse::getPosition(window).x) / window
            .getSize().x);

    angle_ = degCheck(angle_ + rotationHorizontal);

    sf::Mouse::setPosition(sf::Vector2i(windowCenterX, windowCenterY), window);

    // Keyboard check
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        position_.x += cosf(angle_*M_PI/180) * speed_ * dTime;
        position_.y -= sinf(angle_*M_PI/180) * speed_ * dTime;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        position_.x -= cosf(angle_*M_PI/180) * speed_ * dTime;
        position_.y += sinf(angle_*M_PI/180) * speed_ * dTime;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        position_.x += cosf(degCheck(angle_ + 90)*M_PI/180) * speed_ * dTime;
        position_.y -= sinf(degCheck(angle_ + 90)*M_PI/180) * speed_ * dTime;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        position_.x += cosf(degCheck(angle_ - 90)*M_PI/180) * speed_ * dTime;
        position_.y -= sinf(degCheck(angle_ - 90)*M_PI/180) * speed_ * dTime;
    }

    // Crossing rays
    crossing();
}

void Camera::crossing()noexcept
{
    collisionPoints_.clear();
    depths_.clear();
    float curAngle = ((360-angle_) * M_PI / 180) - FOV / 2;
    for (float a = 0; a < NUM_RAYS; a++)
    {
        Vector direction = {cosf(curAngle), sinf(curAngle)};
        direction.normalize();

        float bestLen = maxDist_;
        Vector bestPoint = {(position_.x  + direction.x  * bestLen), (position_.y + direction.y * bestLen)};
        Vector wallPoints;
        std::string bestPointName;

        for(auto& object : world_.getObjects())
        {
            for(int i = 0; i < object.second.getNodes().size(); i++)
            {
                int x1 = i % object.second.getNodes().size();
                int x2 = (i + 1) % object.second.getNodes().size();
                Vector wallPoint1 = object.second.getNodes()[x1];
                Vector wallPoint2 = object.second.getNodes()[x2];
                Vector rayStart = position_;

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

                if (t >= 0 && t <= 1 && u >= 0 )
                {
                    if (u < bestLen)
                    {
                        bestPoint = {static_cast<float>(rayStart.x + u * (rayDir.x - rayStart.x)),
                                                   static_cast<float>(rayStart.y + u * (rayDir.y - rayStart.y))};
                        bestLen = u;
                        bestPointName = object.first;
                        wallPoints = {static_cast<float>(x1),static_cast<float>(x2)};
                    }
                }
            }
        }
        collisionPoints_.push_back({bestPointName, {wallPoints, bestPoint}});
        depths_.push_back(bestLen);

        curAngle += FOV / NUM_RAYS;
    }
}

void Camera::draw(sf::RenderTarget &window) const
{
    sf::CircleShape circle(CELL_SCALE/3);
    circle.setPosition(position_.x * CELL_SCALE, position_.y * CELL_SCALE);
    circle.setOutlineThickness(2);
    circle.setFillColor(sf::Color(255, 100, 196));
    circle.setOutlineColor(sf::Color(252, 248, 243));

    sf::ConvexShape triangle;
    triangle.setPointCount(collisionPoints_.size()+2);
    triangle.setPoint(0, {(position_.x * CELL_SCALE + CELL_SCALE/3),
                          (position_.y * CELL_SCALE + CELL_SCALE/3)});

    for(int i = 0; i < collisionPoints_.size(); i++)
    {
        triangle.setPoint(i+1, {collisionPoints_[i].second.second.x * CELL_SCALE,
                                            collisionPoints_[i].second.second.y * CELL_SCALE});
    }
    triangle.setPoint(collisionPoints_.size()+1, {(position_.x * CELL_SCALE + CELL_SCALE/3),
                                                 (position_.y * CELL_SCALE + CELL_SCALE/3)});

    triangle.setFillColor(sf::Color(0,0,0,0));
    triangle.setOutlineColor(sf::Color::White);
    triangle.setOutlineThickness(3);

    window.draw(triangle);
    window.draw(circle);
}

void Camera::drawWorld(sf::RenderTarget &window) noexcept
{
    sf::RectangleShape segment;
    float segmentWidth = WINDOW_WIDTH / NUM_RAYS;
    float segmentHeightProj = segmentWidth*100;
    float segmentHeight;
    sf::Sprite sprite;


    sf::RectangleShape sky;
    sky.setSize({WINDOW_WIDTH, WINDOW_HEIGHT/2});
    sky.setFillColor(sf::Color(135,206,235));

    sf::RectangleShape floor;
    floor.setSize({WINDOW_WIDTH, WINDOW_HEIGHT/2});
    floor.setPosition(0,(WINDOW_HEIGHT/2));
    floor.setFillColor(sf::Color(162,101,62));

    window.draw(sky);
    window.draw(floor);

    int i = 0;
    for(auto& wall : collisionPoints_)
    {
        if(depths_[i] >= maxDist_)
        {
            i++;
            continue;
        }

        sprite.setTexture(world_.getObjects().find(wall.first)->second.getWallTexture());

        Vector rayEnd = wall.second.second;

        float wallTextureColumn = 0;

        float x = WINDOW_WIDTH / NUM_RAYS;

        if (abs(rayEnd.x - round(rayEnd.x)) < abs(rayEnd.y - round(rayEnd.y)))
        {
            wallTextureColumn = rayEnd.y - std::ceil(rayEnd.y);
        }
        else
        {
            wallTextureColumn = rayEnd.x - std::floorf(rayEnd.x);
        }

        segmentHeight = std::floor(segmentWidth * segmentHeightProj / depths_[i]);
        sprite.setTextureRect(sf::IntRect(static_cast<unsigned short>(std::round(sprite.getTexture()->getSize().x *
        wallTextureColumn)), 0,
                                          5, sprite.getTexture()->getSize().y));
        sprite.setScale(1,segmentHeight/sprite.getTexture()->getSize().y);
        sprite.setPosition(i*segmentWidth, WINDOW_HEIGHT/2 - segmentHeight/2);

        window.draw(sprite);
        i++;
    }
}

Vector Camera::getPosition() const
{
    return position_;
}

float Camera::degCheck(float deg) noexcept
{
    return static_cast<float>(fmod(360 + fmod(deg, 360), 360));
}

float Camera::getAngle() const
{
    return angle_;
}

float Camera::getSpeed() const
{
    return speed_;
}

float Camera::getMaxDist() const
{
    return maxDist_;
}

std::vector<std::pair<std::string,std::pair<Vector, Vector>>> &Camera::getCollisionPoints()
{
    return collisionPoints_;
}

std::vector<float> &Camera::getDepths()
{
    return depths_;
}

World &Camera::getWorld() const
{
    return world_;
}
