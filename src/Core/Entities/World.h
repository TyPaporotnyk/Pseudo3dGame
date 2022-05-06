//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_WORLD_H
#define PSEUDO3DGAME_WORLD_H

//#define world_loader Core::Entities::Loaders::WorldLoader

#include <vector>

#include "2DFigures/Object2D.h"

#include "../Helper/Vector.h"

#include "Loaders/WorldLoader.h"

class World
{
private:
    std::map<std::string ,Object2D> _objects;

    int _windowWidth;
    int _windowHeight;

    int cellScale_;

    sf::Texture _skyTexture;
    sf::Texture _floorTexture;

public:
    explicit World(const std::string& skyTexturePath,
                  const std::string& floorTexturePath, int cellScale, int windowWidth, int windowHeight)noexcept;

    void addObject(const Object2D& object2D);

    void drawMap(sf::RenderTarget& window) const noexcept;

    [[nodiscard]] int getCellScale() const;

    [[nodiscard]] int getWindowWidth() const;

    [[nodiscard]] int getWindowHeight() const;

    [[nodiscard]] const std::map<std::string ,Object2D>& getObjects() const;

    [[nodiscard]] const sf::Texture &getSkyTexture() const;
    [[nodiscard]] const sf::Texture &getFloorTexture() const;
};


#endif //PSEUDO3DGAME_WORLD_H