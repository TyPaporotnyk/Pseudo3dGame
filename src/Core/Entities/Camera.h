//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_CAMERA_H
#define PSEUDO3DGAME_CAMERA_H

#include "../Helper/Vector.h"
#include "World.h"

#include <SFML/Audio.hpp>

#include <thread>

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

    mutable std::vector<std::pair<std::string, Vector>> _collisionPoints;
    std::vector<std::thread> _threads;
    mutable std::vector<float> _depths;

    World& _world;

    void crossing(float dX, float dY, float dTime)noexcept;
    void process(int raysNum, float sightStart, int b) noexcept;

    static float degCheck(float deg) noexcept;

public:
    explicit Camera(World& world,Vector position, float speed, int raysNum, int sight, int angle = 0, float
    maxDist = 25);

    void control(const sf::RenderWindow& window,float dTime, bool cameraPause) noexcept;

    [[nodiscard]]int getAngle() const;
    [[nodiscard]]float getSpeed() const;
    [[nodiscard]]float getMaxDist() const;
    [[nodiscard]]Vector getPosition() const;
    [[nodiscard]]int getRaysNum() const;
    [[nodiscard]]float getSight() const;

    [[nodiscard]]const std::vector<std::pair<std::string, Vector>> &getCollisionPoints() const;
    [[nodiscard]]const std::vector<float> &getDepths() const;

};


#endif //PSEUDO3DGAME_CAMERA_H
