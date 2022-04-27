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
    Vector position_;
    float angle_;
    float speed_;
    float maxDist_;

    std::vector<Vector> collisionPoints_;
    std::vector<double> depths_;

    World& world_;

    void crossing() noexcept;

    [[nodiscard]] float degCheck(float deg);

public:

    explicit Camera(World& world, Vector position = {}, float speed = 5, float angle = 0, float maxDist = 20);

    void setPos(Vector pos);

    void control(const sf::RenderWindow& window, float dTime) noexcept;
    void draw(sf::RenderTarget& window) override;
    void drawWorld(sf::RenderTarget& window);

    Vector getPosition() const;
};


#endif //PSEUDO3DGAME_CAMERA_H
