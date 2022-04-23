//
// Created by Даниил on 11.04.2022.
//

#ifndef PSEUDO3DGAME_VECTOR_H
#define PSEUDO3DGAME_VECTOR_H


struct Vector
{
    float x;
    float y;

    Vector() = default;
    Vector(float x, float y);

    static float length(Vector v1, Vector v2);
    float abs();
    void normalize();

    Vector operator +(const Vector v);

    Vector& operator +=(const Vector v);
};


#endif //PSEUDO3DGAME_VECTOR_H
