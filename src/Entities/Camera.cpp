//
// Created by Даниил on 11.04.2022.
//

#include "Camera.h"

#include <iostream>
#include <cmath>

#include "../Core/ResourceManager.h"

Camera::Camera(World& world_, Vector position, float speed, int raysNum, int sight, int angle, float maxDist) :
world_(world_) ,position_(position), speed_(speed), raysNum_(raysNum), sight_(sight*M_PI/180), angle_(angle), maxDist_
(maxDist)
{ }

void Camera::control(const sf::RenderWindow& window, float dTime, bool cameraRotate) noexcept
{
    // Mouse movement
    float windowCenterX = round(window.getSize().x / 2);
    float windowCenterY = round(window.getSize().y / 2);

    float rotationHorizontal = round(90 * (windowCenterX - sf::Mouse::getPosition(window).x) / window.getSize().x);

    angle_ = degCheck(angle_ + rotationHorizontal);

    sf::Mouse::setPosition(sf::Vector2i(windowCenterX, windowCenterY), window);


    float dCos = cosf((360-angle_)*M_PI/180);
    float dSin = sinf((360-angle_)*M_PI/180);

    // Keyboard check
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        position_.x += speed_ * dCos * dTime;
        position_.y += speed_ * dSin * dTime;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        position_.x -= dCos * speed_ * dTime;
        position_.y -= dSin * speed_ * dTime;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        position_.x += dSin * speed_ * dTime;
        position_.y -= dCos * speed_ * dTime;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        position_.x -= dSin * speed_ * dTime;
        position_.y += dCos * speed_ * dTime;
    }

    // Crossing rays
    crossing();
}

void Camera::crossing()noexcept
{
    collisionPoints_.clear();
    depths_.clear();

    float curAngle = ((360-angle_) * M_PI / 180) - sight_ / 2;

    for (float a = 0; a < raysNum_; a++)
    {
        Vector direction = {cosf(curAngle), sinf(curAngle)};
        direction.normalize();

        float bestLen = maxDist_;
        std::string bestPointName;
        Vector bestPoint = {(position_.x  + direction.x  * bestLen), (position_.y + direction.y * bestLen)};

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
                        bestLen = u;

                        bestPoint = {static_cast<float>(rayStart.x + bestLen * (rayDir.x - rayStart.x)),
                                     static_cast<float>(rayStart.y + bestLen * (rayDir.y - rayStart.y))};
                        bestPointName = object.first;
                    }
                }
            }
        }
        collisionPoints_.emplace_back(bestPointName, bestPoint);
        depths_.push_back(bestLen * cosf(((360-angle_) * M_PI / 180) - curAngle));

        curAngle += sight_ / raysNum_;
    }
}

void Camera::drawSight(sf::RenderTarget &window) const
{
    sf::CircleShape circle(world_.getCellScale()/3);
    circle.setPosition(position_.x * world_.getCellScale(), position_.y * world_.getCellScale());
    circle.setOutlineThickness(2);
    circle.setFillColor(sf::Color(255, 100, 196));
    circle.setOutlineColor(sf::Color(252, 248, 243));

    sf::ConvexShape triangle;
    triangle.setPointCount(collisionPoints_.size()+2);
    triangle.setPoint(0, {(position_.x * world_.getCellScale() + world_.getCellScale()/3),
                          (position_.y * world_.getCellScale() + world_.getCellScale()/3)});

    for(int i = 0; i < collisionPoints_.size(); i++)
    {
        triangle.setPoint(i+1, {collisionPoints_[i].second.x * world_.getCellScale(),
                                collisionPoints_[i].second.y * world_.getCellScale()});
    }
    triangle.setPoint(collisionPoints_.size()+1,
                      {(position_.x * world_.getCellScale() + world_.getCellScale()/3),
                             (position_.y * world_.getCellScale() + world_.getCellScale()/3)});

    triangle.setFillColor(sf::Color(0,0,0,0));
    triangle.setOutlineColor(sf::Color::White);
    triangle.setOutlineThickness(3);

    window.draw(triangle);
    window.draw(circle);
}

void Camera::drawWorld(sf::RenderTarget &window)const noexcept
{
    int segmentWidth = std::ceil(ResourceManager::Window::getWindowWidth() / raysNum_);
    float segmentHeightProj = 100;
    float segmentHeight;
    sf::RectangleShape segment;
    sf::Sprite sprite;

    float d = raysNum_ / 2*tan(sight_/2);

    float offset = -10 * (angle_+1) % world_.getSkyTexture().getSize().x;
    sf::Sprite sky;
    sky.setTexture(world_.getSkyTexture());
    sky.setScale(2,2);

    sky.setTextureRect(sf::IntRect(offset,0,world_.getSkyTexture().getSize().x,
                                   world_.getSkyTexture().getSize().y));
    window.draw(sky);
    sky.setTextureRect(sf::IntRect(offset - ResourceManager::Window::getWindowWidth(),0,
                                   world_.getSkyTexture().getSize().x,world_.getSkyTexture().getSize().y));
    window.draw(sky);
    sky.setTextureRect(sf::IntRect(offset + ResourceManager::Window::getWindowWidth(),0,
                                   world_.getSkyTexture().getSize().x,world_.getSkyTexture().getSize().y));
    window.draw(sky);

    sf::RectangleShape floor;
    floor.setSize({static_cast<float>(ResourceManager::Window::getWindowWidth()),
                   static_cast<float>(ResourceManager::Window::getWindowHeight())/2});
    floor.setPosition(0,(ResourceManager::Window::getWindowHeight()/2));
    floor.setFillColor(sf::Color(162,101,62));

    window.draw(floor);

    Entities entity = Entities::NONE;

    int i = 0;
    for(auto& wall : collisionPoints_)
    {
        if(wall.first == "")
        {
            i++;
            continue;
        }

        segmentHeight = d * segmentHeightProj / depths_[i] / 10;
        float wallTextureColumn = 0;

        Vector rayEnd = wall.second;

        if(entity != world_.getObjects().find(wall.first)->second.getType())
        {
            sprite.setTexture(world_.getObjects().find(wall.first)->second.getWallTexture());
            entity = world_.getObjects().find(wall.first)->second.getType();
        }

        if (abs(rayEnd.x - round(rayEnd.x)) < abs(rayEnd.y - round(rayEnd.y)))
        {
            wallTextureColumn = rayEnd.y - std::ceil(rayEnd.y);
        }
        else
        {
            wallTextureColumn = rayEnd.x - std::floorf(rayEnd.x);
        }

        sprite.setTextureRect(sf::IntRect(sprite.getTexture()->getSize().x * wallTextureColumn,
                                          0,ResourceManager::Window::getWindowWidth()/raysNum_, sprite.getTexture()->getSize
                                          ().y));
        sprite.setScale(1,segmentHeight/sprite.getTexture()->getSize().y);
        sprite.setPosition(i*segmentWidth, ResourceManager::Window::getWindowHeight()/2 - segmentHeight/2);

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

int Camera::getAngle() const
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

int Camera::getRaysNum() const
{
    return raysNum_;
}

float Camera::getSight() const
{
    return sight_;
}

std::vector<std::pair<std::string, Vector>> &Camera::getCollisionPoints()
{
    return collisionPoints_;
}

std::vector<float> &Camera::getDepths()
{
    return depths_;
}
