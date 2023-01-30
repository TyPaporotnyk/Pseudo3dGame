//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_OBJECT2D_H
#define PSEUDO3DGAME_OBJECT2D_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../Helper/Vector.h"

enum class Entities
{
    CUBE,
    CIRCLE,
    PLAYER,
    NONE
};

class Object2D
{
protected:
    std::vector<Vector> _points;
    Vector _position;

    std::string _name;

    sf::Texture& _wallTexture;

    Entities _entity;

public:
    explicit Object2D(std::string name, sf::Texture& wallTexture, Entities entity, Vector position = {},
                      std::vector<Vector>points = {});

    [[nodiscard]] const std::vector<Vector>& getNodes() const;

    void draw(sf::RenderTarget& window, int cellSCale)  const;

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] sf::Texture& getWallTexture() const;

    [[nodiscard]] Entities getType() const;

//    [[nodiscard]]const std::vector<Vector> &getPoints() const;
    [[nodiscard]] const Vector& getPosition() const;
    float getCenter();
};


#endif //PSEUDO3DGAME_OBJECT2D_H
