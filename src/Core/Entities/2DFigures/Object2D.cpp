//
// Created by Даниил on 11.04.2022.
//

#include "Object2D.h"

#include <utility>

Object2D::Object2D(std::string name, sf::Texture& wallTexture, Entities entity, Vector position,
                   std::vector<Vector>points) :
name_(std::move(name)), wallTexture_(wallTexture), entity_(entity), position_(position), points_(std::move(points))
{
    for(auto& p : this->points_)
    {
        p += position;
    }
}

void Object2D::draw(sf::RenderTarget &window, int cellScale) const
{
    sf::ConvexShape figure;
    figure.setPointCount(points_.size());

    for(int i = 0; i < points_.size(); i++)
    {
        figure.setPoint(i, {points_[i].x * cellScale, points_[i].y * cellScale});
    }

    figure.setFillColor(sf::Color(255, 228, 196));

    window.draw(figure);
}

const std::vector<Vector> & Object2D::getNodes() const
{
    return points_;
}

const Vector &Object2D::getPosition() const
{
    return position_;
}

const std::string &Object2D::getName() const
{
    return name_;
}

sf::Texture & Object2D::getWallTexture() const
{
    return wallTexture_;
}

Entities Object2D::getType() const
{
    return entity_;
}
