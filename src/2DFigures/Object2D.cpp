//
// Created by Даниил on 11.04.2022.
//

#include "Object2D.h"

#include "../Settings.h"

Object2D::Object2D(Vector position, std::vector<Vector> points) :
points(points)
{
    for(auto& p : this->points){
        p += position;
    }
}

void Object2D::draw(sf::RenderTarget &window)
{
    sf::ConvexShape figure;
    figure.setPointCount(points.size());

    for(int i = 0; i < points.size(); i++)
    {
        figure.setPoint(i, {points[i].x * CELL_SCALE, points[i].y * CELL_SCALE});
    }

    figure.setFillColor(sf::Color(255, 228, 196));
    figure.setOutlineColor(sf::Color(252, 248, 243));
//    figure.setOutlineThickness(5);

    window.draw(figure);
}

std::vector<Vector> &Object2D::getNodes()
{
    return points;
}