//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_OBJECT2D_H
#define PSEUDO3DGAME_OBJECT2D_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../Resources/Vector.h"

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
    std::vector<Vector>points_;
    Vector position_;

    std::string name_;

    sf::Texture& wallTexture_;

    Entities entity_;

public:
    explicit Object2D(std::string name, sf::Texture& wallTexture, Entities entity, Vector position = {},
                      std::vector<Vector>points = {});

    std::vector<Vector>& getNodes();

    void draw(sf::RenderTarget &window, int cellSCale) const;

    [[nodiscard]]const std::string &getName() const;
    [[nodiscard]]sf::Texture & getWallTexture() const;

    [[nodiscard]]Entities getType() const;

    [[nodiscard]]const std::vector<Vector> &getPoints() const;
    [[nodiscard]]const Vector &getPosition() const;
};


#endif //PSEUDO3DGAME_OBJECT2D_H
