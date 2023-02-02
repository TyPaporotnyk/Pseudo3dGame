//
// Created by Даниил on 11.04.2022.
//

#include "Camera.h"

#include <iostream>
#include <cmath>
#include <utility>

#include "../../Precompiler.h"

//#define MULTITHREADING
//#define COLLISIONS

Camera::Camera(World &_world, Vector position, float speed, int raysNum, int sight, int angle, float maxDist) :
        _world(_world), _position(position), _speed(speed), _raysNum(raysNum), _sight(sight * M_PI / 180),
        _angle(angle), _maxDist(maxDist)
{
    _collisionPoints.resize(raysNum);
    _depths.resize(raysNum);

    _walkSound.setBuffer(*RESOURCE_MANAGER.loadSound(std::string(DATA_DIR + std::string("/sound/steps.ogg"))));
    _walkSound.setLoop(true);
    _walkSound.setVolume(50.f);
    _walkSound.setPitch(0.8);

    _threads = std::vector<std::thread>(std::thread::hardware_concurrency());
}

void Camera::control(const sf::RenderWindow &window, float dTime, bool cameraPause) noexcept
{
    // Mouse movement
    if (cameraPause)
    {
        return;
    }

    float windowCenterX = round(window.getSize().x / 2);
    float windowCenterY = round(window.getSize().y / 2);

    float rotationHorizontal = 120 * (windowCenterX - sf::Mouse::getPosition(window).x) / window.getSize().x;

    _angle = degCheck(round(_angle + rotationHorizontal));

    sf::Mouse::setPosition(sf::Vector2i(windowCenterX, windowCenterY), window);

    float dCos = cosf((360 - _angle) * M_PI / 180);
    float dSin = sinf((360 - _angle) * M_PI / 180);

    float dX = 0;
    float dY = 0;

    // Keyboard check
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        dX += dCos;
        dY += dSin;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        dX -= dCos;
        dY -= dSin;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        dX += dSin;
        dY -= dCos;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        dX -= dSin;
        dY += dCos;
    }

    if (dX != 0 || dY != 0)
    {
        if (_walkSound.getStatus() != sf::Sound::Status::Playing)
        {
            _walkSound.setPitch(0.8);
            _walkSound.play();
        }
    } else
    {
        _walkSound.pause();
    }

    crossing(dX * _speed * dTime, dY * _speed * dTime, dTime);
}

std::vector<std::pair<std::string, std::shared_ptr<Object2D>>> Camera::getObjectsInView(Vector direction)
{
    std::vector<std::pair<std::string, std::shared_ptr<Object2D>>> objectsInView;
    for (auto &object: _world.getObjects())
    {
        bool inView = false;
        for (Vector node: object.second->getNodes())
        {
            Vector vectorToNode = node - _position;
            vectorToNode.normalize();
            float scalar = direction.x * vectorToNode.x + direction.y * vectorToNode.y;
            if (scalar > 0)
            {
                inView = true;
                break;
            }
        }

        if (inView)
        {
            objectsInView.push_back({object.first, object.second});
        }
    }
    return objectsInView;
}

void Camera::crossing(float dX, float dY, float dTime) noexcept
{
    Vector vector = {dX, dY};
    float curAngle = ((360 - _angle) * M_PI / 180) - _sight / 2;
    float curBackAngle = (_angle * M_PI / 180) - (360 - _sight) / 2;

//    _collisionPoints.clear();
    for (int a = 0, da = 0; a < _raysNum; a++, da++)
    {
        Vector direction = {cosf(curAngle), sinf(curAngle)};
        Vector backDirection = {cosf(curBackAngle), sinf(curBackAngle)};
        direction.normalize();

        Point bestPoint = {"", _maxDist,
                           {(_position.x + direction.x * _maxDist),
                            (_position.y + direction.y * _maxDist)}, 0};

        for (auto &object: getObjectsInView(direction))
        {
            for (int i = 0; i < object.second->getNodes().size(); i++)
            {
                int x1 = i % object.second->getNodes().size();
                int x2 = (i + 1) % object.second->getNodes().size();

                Vector point1 = object.second->getNodes()[x1];
                Vector point2 = object.second->getNodes()[x2];

                Point crossPoint = cross(direction, point1, point2);

                if (crossPoint.rayNum == -1)
                {
                    continue;
                } else if (crossPoint.depth < bestPoint.depth)
                {
                    crossPoint.name = object.first;
                    crossPoint.rayNum = a;
                    bestPoint = crossPoint;

                    collision(vector, point1, point2, bestPoint.depth);
                }
            }
        }

        if (da < _raysNum/4)
        {
            for (auto &object: getObjectsInView(backDirection))
            {
                for (int i = 0; i < object.second->getNodes().size(); i++)
                {
                    int x1 = i % object.second->getNodes().size();
                    int x2 = (i + 1) % object.second->getNodes().size();

                    Vector point1 = object.second->getNodes()[x1];
                    Vector point2 = object.second->getNodes()[x2];

                    Point crossPoint = cross(backDirection, point1, point2);

                    if (crossPoint.rayNum == -1)
                    {
                        continue;
                    }

                    collision(vector, point1, point2, crossPoint.depth);
                }
            }
        }

        bestPoint.depth *= cosf(((360 - _angle) * M_PI / 180) - curAngle);
        _collisionPoints[a] = bestPoint;

        curAngle += _sight / _raysNum;
        curBackAngle += (360 - _sight) / _raysNum / 4;
    }

    _position += vector;
}

Vector Camera::collision(Vector &moveTo, Vector point1, Vector point2, float depth) noexcept
{
    Vector edge = point2 - point1;
    Vector normal = {edge.y, -edge.x};
    normal.normalize();

    Vector toWallVector = point1 + point2 - _position * 2;

    if ((normal * toWallVector).x > 0 && (normal * toWallVector).y > 0)
        normal = normal * (-1);

    float scalar = moveTo.x * normal.x + moveTo.y * normal.y;

    if (scalar < 0 && abs(depth - abs(scalar)) < 0.3)
    {
        moveTo.x -= normal.x * scalar;
        moveTo.y -= normal.y * scalar;
    }
}

Point Camera::cross(Vector direction, Vector point1, Vector point2) noexcept
{
    Vector rayStart = _position;
    Vector rayDir = rayStart + direction;

    float den = (point1.x - point2.x) * (rayStart.y - rayDir.y) -
                (point1.y - point2.y) * (rayStart.x - rayDir.x);

    if (den != 0)
    {
        float t = ((point1.x - rayStart.x) * (rayStart.y - rayDir.y) -
                   (point1.y - rayStart.y) * (rayStart.x - rayDir.x)) / den;
        float dist = -((point1.x - point2.x) * (point1.y - rayStart.y) -
                       (point1.y - point2.y) * (point1.x - rayStart.x)) / den;

        if (t >= 0 && t <= 1 && dist >= 0)
        {
            Vector position = {static_cast<float>(rayStart.x + dist * (rayDir.x - rayStart.x)),
                               static_cast<float>(rayStart.y + dist * (rayDir.y - rayStart.y))};
            return {"", dist, position, 0};
        }
    }
    return {"", 0, Vector(), -1};
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

const std::vector<Point> &Camera::getCollisionPoints() const
{
    return _collisionPoints;
}
