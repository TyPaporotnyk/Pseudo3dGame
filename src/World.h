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
    std::vector<Object2D> objects_;

public:
    explicit World(std::vector<Object2D> objects = {}) noexcept;

    Vector loadMapFromImage(std::string& imgPath) noexcept;
    void addObject(const Object2D& object2D) noexcept;

    void draw(sf::RenderTarget& window) const override;

    [[nodiscard]]std::vector<Object2D>& getObjects();
};


#endif //PSEUDO3DGAME_WORLD_H
