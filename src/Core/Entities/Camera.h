//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_CAMERA_H
#define PSEUDO3DGAME_CAMERA_H

#include "../Helper/Vector.h"
#include "World.h"
#include "2DFigures/Object2D.h"

#include <SFML/Audio.hpp>

#include <thread>
#include <vector>

struct Point
{
    std::string name;
    float depth;
    Vector position;
    int rayNum;
};

class Camera
{
private:
    Vector _position;
    int _angle;
    int _raysNum;
    float _sight;
    float _speed;
    float _maxDist;

    bool texturing = true;


    sf::Sound _walkSound;

    mutable std::vector<Point> _collisionPoints;
    std::vector<std::thread> _threads;
    mutable std::vector<float> _depths;

    World &_world;

    std::vector<std::pair<std::string, std::shared_ptr<Object2D>>> getObjectsInView(Vector direction);

    void crossing(float dX, float dY, float dTime) noexcept;

    Point cross(Vector direction, Vector point1, Vector point2) noexcept;

    Vector collision(Vector &moveTo, Vector point1, Vector point2, float depth) noexcept;

    static float degCheck(float deg) noexcept;

public:
    explicit Camera(World &world, Vector position, float speed, int raysNum, int sight, int angle = 0, float
    maxDist = 25);

    void control(const sf::RenderWindow &window, float dTime, bool cameraPause) noexcept;

    [[nodiscard]]int getAngle() const;

    [[nodiscard]]float getSpeed() const;

    [[nodiscard]]float getMaxDist() const;

    [[nodiscard]]Vector getPosition() const;

    [[nodiscard]]int getRaysNum() const;

    [[nodiscard]]float getSight() const;

    [[nodiscard]]const std::vector<Point> &getCollisionPoints() const;

    [[nodiscard]]const std::vector<float> &getDepths() const;

};


#endif //PSEUDO3DGAME_CAMERA_H
