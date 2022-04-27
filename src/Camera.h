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
    float maxDist;

    std::vector<Vector> collisionPoints;
    std::vector<double> depths;

    World& world;

    void crossing() noexcept;

    [[nodiscard]] float degCheck(float deg);

public:

    explicit Camera(World& world, Vector position = {}, float speed = 5, float angle = 0, float maxDist = 20);

    void setPos(Vector pos);

    void control(const sf::RenderWindow& window) noexcept;
    void draw(sf::RenderTarget& window) override;
    void drawWorld(sf::RenderTarget& window);
};


#endif //PSEUDO3DGAME_CAMERA_H
