//
// Created by Даниил on 25.04.2022.
//

#ifndef PSEUDO3DGAME_CIRCLE_H
#define PSEUDO3DGAME_CIRCLE_H

#include "Object2D.h"


class Circle :  public Object2D
{
private:
    float _radius;

public:
    explicit Circle(std::string name, sf::Texture& wallTexture, Vector position = {}, float radius = 1);

    void draw(sf::RenderTarget &window) const;
};


#endif //PSEUDO3DGAME_CIRCLE_H
