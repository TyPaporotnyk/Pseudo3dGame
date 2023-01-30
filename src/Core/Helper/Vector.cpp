//
// Created by Даниил on 11.04.2022.
//

#include "Vector.h"

#include <cmath>

Vector::Vector(float x, float y)
: x(x), y(y)
{

}

Vector Vector::operator+(float v)
{
    return {x + v, y + v};
}

Vector Vector::operator+(Vector v)
{
    return {x + v.x, y + v.y};
}

Vector Vector::operator-(Vector v)
{
    return {x - v.x, y - v.y};
}

Vector Vector::operator*(float n)
{
    return {x + n, y + n};
}

Vector Vector::operator*(Vector v)
{
    return {x * v.x, y * v.y};
}

Vector &Vector::operator+=(Vector v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector &Vector::operator*=(Vector v)
{
    this->x *= v.x;
    this->y *= v.y;
    return *this;
}

Vector &Vector::operator*=(float n)
{
    this->x *= n;
    this->y *= n;
    return *this;;
}

Vector &Vector::operator/=(float n)
{
    this->x /= n;
    this->y /= n;
    return *this;
}

float Vector::length(Vector v1, Vector v2)
{
    return sqrt(pow(v2.x - v1.x,2) + pow(v2.y - v1.y,2));
}

float Vector::abs(Vector v1, Vector v2)
{
    return sqrt(v1.x*v2.x + v1.y*v2.y);
}

void Vector::normalize()
{
    float len = abs({x,y}, {x,y});
    x /= len;
    y /= len;
}
