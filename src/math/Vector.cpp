#include <cmath>
#include "../glcraft.hpp"

const Vector* Vector::add(const Vector* b) {
    x += b->x;
    y += b->y;
    z += b->z;

    return this;
}

const Vector* Vector::invert() {
    x = -x;
    y = -y;
    z = -z;

    return this;
}

const Vector* Vector::scale(float s) {
    x *= s;
    y *= s;
    z *= s;

    return this;
}

float Vector::length() const {
    return sqrt(x*x + y*y + z*z);
}

const Vector* Vector::norm() {
    scale(1.0f/length());
    return this;
}

/// Векторное произведение векторов
std::unique_ptr<Vector> Vector::cross(const Vector* b) {
    auto a = this;
    return std::make_unique<Vector>(a->y * b->z - a->z * b->y,
                                    a->z * b->x - a->x * b->z,
                                    a->x * b->y - a->y * b->x);
}

std::unique_ptr<Vector> Vector::copy() const {
    return std::make_unique<Vector>(*this);
}


void Vector::pack4(std::vector<float>* vector) {
    vector->push_back(x);
    vector->push_back(y);
    vector->push_back(z);
    vector->push_back(w);
}

void Vector::pack3(std::vector<float>* vector) {
    vector->push_back(x);
    vector->push_back(y);
    vector->push_back(z);
}

void Vector::pack2(std::vector<float>* vector) {
    vector->push_back(x);
    vector->push_back(y);
}
