#include <cmath>
#include "../glcraft.hpp"

const Vector* Vector::add(const Vector* b) {
    x += b->x;
    y += b->y;
    z += b->z;

    return this;
}

const Vector* Vector::invert(const Vector* b) {
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
    float len = length();

    x /= len;
    y /= len;
    z /= len;

    return this;
}

/// Векторное произведение векторов
const Vector* Vector::cross(const Vector* b) {
    auto a = this->copy();

    x = a->y * b->z - a->z * b->y;
    y = a->z * b->x - a->x * b->z;
    z = a->x * b->y - a->y * b->x;

    return this;
}

std::unique_ptr<Vector> Vector::copy() const {
    return std::make_unique<Vector>(*this);
}