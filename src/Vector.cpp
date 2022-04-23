//
// Created by Даниил on 11.04.2022.
//

#include "Vector.h"

#include <cmath>

Vector::Vector(float x, float y)
: x(x), y(y)
{

}

Vector Vector::operator+(const Vector v)
{
    return Vector(this->x + v.x, this->y + v.y);
}

Vector &Vector::operator+=(const Vector v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;;
}

float Vector::length(Vector v1, Vector v2)
{
    return sqrt(pow(v1.x - v2.x,2) + pow(v1.y - v2.y,2));
}

float Vector::abs()
{
    return sqrt(x*x + y*y);
}

void Vector::normalize()
{
    float len = abs();
    x /= len;
    y /= len;
}
