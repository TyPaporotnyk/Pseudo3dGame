//
// Created by Даниил on 25.04.2022.
//

#ifndef PSEUDO3DGAME_CIRCLE_H
#define PSEUDO3DGAME_CIRCLE_H

#include "Object2D.h"

#include "../Vector.h"

class Circle :  public Object2D
{
public:
    Circle(Vector position, float radius = 1);

};


#endif //PSEUDO3DGAME_CIRCLE_H
