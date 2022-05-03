//
// Created by Даниил on 11.04.2022.
//

#include "Camera.h"

#include <iostream>
#include <cmath>

Camera::Camera(World& world_, Vector position, float speed, int raysNum, int sight, int angle, float maxDist) :
world_(world_) ,position_(position), speed_(speed), raysNum_(raysNum), sight_(sight*M_PI/180), angle_(angle), maxDist_
(maxDist)
{
    collisionPoints_.resize(raysNum);
    depths_.resize(raysNum);
}

void Camera::control(const sf::RenderWindow& window, float dTime, bool cameraPause) noexcept
{
    // Mouse movement
    if(cameraPause)
    {
        return;
    }

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
        collisionPoints_[a] = {bestPointName, bestPoint};
        depths_[a] = (bestLen * cosf(((360-angle_) * M_PI / 180) - curAngle));

        curAngle += sight_ / raysNum_;
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

const std::vector<std::pair<std::string, Vector>> &Camera::getCollisionPoints() const
{
    return collisionPoints_;
}

const std::vector<float> &Camera::getDepths() const
{
    return depths_;
}
