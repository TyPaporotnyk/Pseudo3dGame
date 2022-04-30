//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_WORLD_H
#define PSEUDO3DGAME_WORLD_H

#include <vector>

#include "2DFigures/Object2D.h"
#include "IDrawble.h"
#include "Vector.h"


class World : public virtual IDrawable
{
private:
    std::map<std::string ,Object2D> objects_;

    sf::Texture skyTexture_;
    sf::Sprite skySprite_;

    sf::Texture floorTexture_;
    sf::Sprite floorSprite_;

public:
    explicit World(const std::string& skyTexturePath = " ",
                  const std::string& floorTexturePath = " ")noexcept;

    Vector loadMapFromImage(const std::string& worldPath) noexcept;
    void addObject(const Object2D& object2D) noexcept;

    void draw(sf::RenderTarget& window) const override;

    [[nodiscard]]std::map<std::string ,Object2D>& getObjects();

    [[nodiscard]]sf::Texture &getSkyTexture();
    [[nodiscard]]sf::Texture &getFloorTexture();
};


#endif //PSEUDO3DGAME_WORLD_H
