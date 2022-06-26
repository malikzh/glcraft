//
// Created by malikzh on 26.06.2022.
//

#ifndef GLCRAFT_VECTOR_HPP
#define GLCRAFT_VECTOR_HPP


class Vector {
public:
    float x;
    float y;
    float z;
    float w;

    Vector() : Vector(0.0f, 0.0f, 0.0f) {}
    Vector(float _x, float _y, float _z, float _w = 1.0f) : x(_x), y(_y), z(_z), w(_w) {}
    Vector(const Vector& v) : Vector(v.x, v.y, v.z, v.w) {}

    const Vector* add(const Vector* b);
    const Vector* invert(const Vector* b);
    const Vector* scale(float s);
    float length() const;
    const Vector* norm();
    const Vector* cross(const Vector* b);
    std::unique_ptr<Vector> copy() const;
};


#endif //GLCRAFT_VECTOR_HPP
