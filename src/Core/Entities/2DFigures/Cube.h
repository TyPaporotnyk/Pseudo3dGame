//
// Created by Даниил on 24.04.2022.
//

#ifndef PSEUDO3DGAME_CUBE_H
#define PSEUDO3DGAME_CUBE_H

#include "Object2D.h"

#include "../../../Helper/Vector.h"

class Cube : public Object2D
{
private:
    int scale_;

public:
    explicit Cube(std::string name, sf::Texture& wallTexture, Vector position = {},
                  const std::vector<Vector>&points = {}, int scale = 1);

    void draw(sf::RenderTarget &window) const;
};


#endif //PSEUDO3DGAME_CUBE_H
