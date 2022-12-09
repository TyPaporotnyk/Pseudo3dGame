//
// Created by Даниил on 11.04.2022.
//

#include "Camera.h"

#include <iostream>
#include <cmath>

#include "../../Precompiler.h"

//#define MULTITHREADING
#define COLLISIONS

Camera::Camera(World& _world, Vector position, float speed, int raysNum, int sight, int angle, float maxDist) :
_world(_world) ,_position(position), _speed(speed), _raysNum(raysNum), _sight(sight*M_PI/180), _angle(angle), _maxDist
(maxDist)
{
    _collisionPoints.resize(raysNum);
    _depths.resize(raysNum);

    _walkSound.setBuffer(*RESOURCE_MANAGER.loadSound(std::string(DATA_DIR + std::string("/sound/steps.ogg"))));
    _walkSound.setLoop(true);
    _walkSound.setVolume(50.f);
    _walkSound.setPitch(0.8);

    _threads = std::vector<std::thread>(std::thread::hardware_concurrency());
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

    _angle = degCheck(_angle + rotationHorizontal);

    sf::Mouse::setPosition(sf::Vector2i(windowCenterX, windowCenterY), window);

    float dCos = cosf((360-_angle)*M_PI/180);
    float dSin = sinf((360-_angle)*M_PI/180);

    float dX = 0;
    float dY = 0;

    float shiftSpeed = 1.0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        shiftSpeed = 1.75;
    }

    // Keyboard check
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        dX += dCos;
        dY += dSin;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        dX -= dCos;
        dY -= dSin;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        dX += dSin;
        dY -= dCos;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        dX -= dSin;
        dY += dCos;
    }

    if(dX != 0 || dY != 0)
    {
        if (_walkSound.getStatus() != sf::Sound::Status::Playing)
        {
            _walkSound.setPitch(0.8);
            _walkSound.play();
        }
    }
    else
    {
        _walkSound.pause();
    }

    // Crossing rays by thread but without collisions
#ifdef MULTITHREADING
    for(unsigned int i = 0; i < _threads.size(); i++)
    {
        _threads[i] = std::thread([this](int raysNum, float sightStart, int b) noexcept
        {
            float curAngle = (((360-_angle) * M_PI / 180) - _sight / 2) + sightStart;

            for (float a = 0; a < raysNum; a++)
            {
                Vector direction = {cosf(curAngle), sinf(curAngle)};
                direction.normalize();

                float bestLen = _maxDist;
                std::string bestPointName;
                Vector bestPoint = {(_position.x  + direction.x  * bestLen),
                                    (_position.y + direction.y * bestLen)};

                for(auto& object : _world.getObjects())
                {
                    for(int i = 0; i < object.second->getNodes().size(); i++)
                    {
                        int x1 = i % object.second->getNodes().size();
                        int x2 = (i + 1) % object.second->getNodes().size();

                        Vector wallPoint1 = object.second->getNodes()[x1];
                        Vector wallPoint2 = object.second->getNodes()[x2];

                        Vector rayStart = _position;
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
                _collisionPoints[b+a] = {bestPointName, bestPoint};
                _depths[b+a] = (bestLen * cosf(((360-_angle) * M_PI / 180) - curAngle));

                curAngle += _sight / _raysNum;
            }
        }, _raysNum/_threads.size(), ((_sight / _raysNum)*(_raysNum/_threads.size()))*i, _raysNum/_threads.size()*i);
    }

    for (auto& t:_threads)
    {
        t.join();
    }

    _position.x += dX * _speed * dTime;
    _position.y += dY * _speed * dTime;
#endif
    // Crossing rays without thread
#ifndef MULTITHREADING
    crossing(dX * _speed * shiftSpeed * dTime, dY * _speed * shiftSpeed * dTime, dTime);
#endif
}

void Camera::crossing(float dX, float dY, float dTime)noexcept
{
    Vector vector = {dX, dY};

    cross(dX, dY);

    _position += vector;
}

void Camera::cross(float dX, float dY) noexcept
{
    float curAngle = ((360-_angle) * M_PI / 180) - _sight / 2;
    float angle = (360-_angle) * M_PI / 180;

    Vector vector = {dX, dY};

    for (float a = 0, dA = 0; a < _raysNum && dA < _raysNum; a++, dA++)
    {
        Vector direction = {cosf(curAngle), sinf(curAngle)};
        direction.normalize();

        float bestLen = _maxDist;
        std::string bestPointName;
        Vector bestPoint = {(_position.x  + direction.x  * bestLen), (_position.y + direction.y * bestLen)};

        for(auto& object : _world.getObjects())
        {
            for(int i = 0; i < object.second->getNodes().size(); i++)
            {
                int x1 = i % object.second->getNodes().size();
                int x2 = (i + 1) % object.second->getNodes().size();

                Vector wallPoint1 = object.second->getNodes()[x1];
                Vector wallPoint2 = object.second->getNodes()[x2];

                Vector rayStart = _position;
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

#ifdef COLLISIONS
                        Vector edge = wallPoint2 - wallPoint1;
                        Vector normal = {edge.y, -edge.x};
                        normal.normalize();

                        Vector toWallVector = wallPoint1 + wallPoint2 - _position*2;

                        if((normal * toWallVector).x > 0 && (normal * toWallVector).y > 0)
                            normal = normal * -1;

                        float scalar = vector.x * normal.x + vector.y * normal.y;

                        if (scalar < 0 && abs(u - abs(scalar)) < 0.5)
                        {
                            vector.x -= normal.x * scalar;
                            vector.y -= normal.y * scalar;
                        }
#endif
#ifndef COLLISIONS
                        vector = {dX,dY};
#endif
                    }
                }

            }
        }
        _collisionPoints[a] = {bestPointName, bestPoint};
        _depths[a] = (bestLen * cosf(((360-_angle) * M_PI / 180) - curAngle));

        curAngle += _sight / _raysNum;
        angle += M_PI * 2 / _raysNum;
    }
}

Vector Camera::getPosition() const
{
    return _position;
}

float Camera::degCheck(float deg) noexcept
{
    return static_cast<float>(fmod(360 + fmod(deg, 360), 360));
}

int Camera::getAngle() const
{
    return _angle;
}

float Camera::getSpeed() const
{
    return _speed;
}

float Camera::getMaxDist() const
{
    return _maxDist;
}

int Camera::getRaysNum() const
{
    return _raysNum;
}

float Camera::getSight() const
{
    return _sight;
}

const std::vector<std::pair<std::string, Vector>> &Camera::getCollisionPoints() const
{
    return _collisionPoints;
}

const std::vector<float> &Camera::getDepths() const
{
    return _depths;
}
