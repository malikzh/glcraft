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
    Vector(float _x, float _y, float _z = 0.0f, float _w = 1.0f) : x(_x), y(_y), z(_z), w(_w) {}
    Vector(const Vector& v) : Vector(v.x, v.y, v.z, v.w) {}

    const Vector* add(const Vector* b);
    const Vector* invert();
    const Vector* scale(float s);
    [[nodiscard]] float length() const;
    const Vector* norm();
    std::unique_ptr<Vector> cross(const Vector* b);
    [[nodiscard]] std::unique_ptr<Vector> copy() const;
    void pack4(std::vector<float>* vector) const;
    void pack3(std::vector<float>* vector) const;
    void pack2(std::vector<float>* vector) const;
    const Vector* apply(const Matrix* m);
    const Vector* set(const Vector* v);
    const Vector* reset();
};


#endif //GLCRAFT_VECTOR_HPP
