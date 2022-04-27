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
    std::vector<Object2D> objects;
//    Object2D object;

public:

    explicit World(std::vector<Object2D> objects = {});

    void draw(sf::RenderTarget& window) override;
    void addObject(Object2D object2D);

    Vector loadMapFromImage(std::string imgPath);

    std::vector<Object2D>& getObjects();


};


#endif //PSEUDO3DGAME_WORLD_H
