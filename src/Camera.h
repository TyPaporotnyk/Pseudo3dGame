//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_CAMERA_H
#define PSEUDO3DGAME_CAMERA_H

#include "IDrawble.h"
#include "Vector.h"
#include "World.h"

class Camera : public virtual IDrawable
{
private:
    Vector position;
    float angle;
    float speed;

    std::vector<Vector> collisionPoints;

    World& world;

    void crossing() noexcept;

    [[nodiscard]] float degCheck(int deg);

public:

    explicit Camera(World& world, Vector position = {}, float speed = 5, float angle = 0 );

    void control(const sf::RenderWindow& window) noexcept;
    void draw(sf::RenderTarget& window) override;
};


#endif //PSEUDO3DGAME_CAMERA_H
