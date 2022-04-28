//
// Created by Даниил on 11.04.2022.
//

#include "Object2D.h"

#include "../Settings.h"

Object2D::Object2D(Vector position, std::vector<Vector> points) :
position_(position), points_(std::move(points))
{
    for(auto& p : this->points_){
        p += position;
    }
}

void Object2D::draw(sf::RenderTarget &window) const
{
    sf::ConvexShape figure;
    figure.setPointCount(points_.size());

    for(int i = 0; i < points_.size(); i++)
    {
        figure.setPoint(i, {points_[i].x * CELL_SCALE, points_[i].y * CELL_SCALE});
    }

    figure.setFillColor(sf::Color(255, 228, 196));

    window.draw(figure);
}

std::vector<Vector> &Object2D::getNodes()
{
    return points_;
}

const std::vector<Vector> &Object2D::getPoints() const
{
    return points_;
}

const Vector &Object2D::getPosition() const
{
    return position_;
}
