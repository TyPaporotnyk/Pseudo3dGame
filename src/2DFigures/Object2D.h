//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_OBJECT2D_H
#define PSEUDO3DGAME_OBJECT2D_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../IDrawble.h"
#include "../Vector.h"

class Object2D : public virtual IDrawable
{
private:
    std::vector<Vector>points;
    Vector position;

public:
    Object2D(Vector position = {}, std::vector<Vector> points = {});

    std::vector<Vector>& getNodes();

    void draw(sf::RenderTarget &window) override;


};


#endif //PSEUDO3DGAME_OBJECT2D_H
