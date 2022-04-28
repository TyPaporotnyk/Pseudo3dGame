//
// Created by Даниил on 24.04.2022.
//

#ifndef PSEUDO3DGAME_CUBE_H
#define PSEUDO3DGAME_CUBE_H

#include "Object2D.h"

#include "../Vector.h"

class Cube : public Object2D
{
public:
    explicit Cube(Vector position = {}, int scale = 1);

    void draw(sf::RenderTarget &window) const override;
};


#endif //PSEUDO3DGAME_CUBE_H
