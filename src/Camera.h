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

    std::vector<std::pair<std::string,std::pair<Vector, Vector>>> collisionPoints_;
    std::vector<float> depths_;

    World& world_;

    void crossing()noexcept;

    static float degCheck(float deg) noexcept;

public:
    explicit Camera(World& world, Vector position = {}, float speed = 5, float angle = 0, float maxDist = 20);

    void control(const sf::RenderWindow& window, float dTime) noexcept;
    void draw(sf::RenderTarget& window) const override;
    void drawWorld(sf::RenderTarget& window) noexcept;

    [[nodiscard]]float getAngle() const;
    [[nodiscard]]float getSpeed() const;
    [[nodiscard]]float getMaxDist() const;
    [[nodiscard]]Vector getPosition() const;

    [[nodiscard]]std::vector<std::pair<std::string,std::pair<Vector, Vector>>> &getCollisionPoints();
    [[nodiscard]]std::vector<float> &getDepths();

    [[nodiscard]]World &getWorld() const;
};


#endif //PSEUDO3DGAME_CAMERA_H
