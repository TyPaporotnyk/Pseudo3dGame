//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_WORLD_H
#define PSEUDO3DGAME_WORLD_H

//#define world_loader Core::Entities::Loaders::WorldLoader

#include <vector>

#include "2DFigures/Object2D.h"

#include "../../Helper/Vector.h"

#include "Loaders/WorldLoader.h"

class World
{
private:
    std::map<std::string ,Object2D> objects_;

    int cellScale_;

    sf::Texture skyTexture_;

    sf::Texture floorTexture_;

public:
    explicit World(const std::string& skyTexturePath,
                  const std::string& floorTexturePath, int cellScale)noexcept;

    void addObject(const Object2D& object2D);

    void drawMap(sf::RenderTarget& window) const noexcept;

    [[nodiscard]]int getCellScale() const;

    [[nodiscard]]const std::map<std::string ,Object2D>& getObjects() const;

    [[nodiscard]]const sf::Texture &getSkyTexture() const;
    [[nodiscard]]const sf::Texture &getFloorTexture() const;
};


#endif //PSEUDO3DGAME_WORLD_H
