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

    Vector operator +(float v);
    Vector operator +(Vector v);
    Vector operator *(float n);
    Vector operator *(Vector v);

    Vector& operator +=(Vector v);
    Vector& operator *=(Vector v);
    Vector& operator *=(float n);

    static float length(Vector v1, Vector v2);

    [[nodiscard]]float abs() const;
    void normalize();
};


#endif //PSEUDO3DGAME_VECTOR_H
