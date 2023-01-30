//
// Created by Даниил on 11.04.2022.
//

#include "Object2D.h"

#include <utility>

Object2D::Object2D(std::string name, sf::Texture& wallTexture, Entities entity, Vector position,
                   std::vector<Vector>points) :
_name(std::move(name)), _wallTexture(wallTexture), _entity(entity), _position(position), _points(std::move(points))
{
    for(auto& p : this->_points)
    {
        p += position;
    }
}

void Object2D::draw(sf::RenderTarget &window, int cellScale) const
{
    sf::ConvexShape figure;
    figure.setPointCount(_points.size());

    for(int i = 0; i < _points.size(); i++)
    {
        figure.setPoint(i, {_points[i].x * cellScale, _points[i].y * cellScale});
    }

    figure.setFillColor(sf::Color(255, 228, 196));

    window.draw(figure);
}

float getCenter();

const std::vector<Vector> & Object2D::getNodes() const
{
    return _points;
}

const Vector &Object2D::getPosition() const
{
    return _position;
}

const std::string &Object2D::getName() const
{
    return _name;
}

sf::Texture & Object2D::getWallTexture() const
{
    return _wallTexture;
}

Entities Object2D::getType() const
{
    return _entity;
}
