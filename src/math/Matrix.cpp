#include <cmath>
#include "../glcraft.hpp"

Matrix::Matrix(const std::initializer_list<float>& values) {
    if (values.size() != 16) {
        throw std::runtime_error("Matrix initializer list size must be 16");
    }

    size_t i =0;
    for (float value : values) {
        data[i++] = value;
    }
}

Matrix::Matrix(const Matrix& matrix) {
    for (size_t i=0; i<size; ++i) {
        data[i] = matrix.data[i];
    }
}

const Matrix* Matrix::reset() {
    for (float & value : data) {
        value = 0.0f;
    }

    return this;
}


const Matrix* Matrix::identity() {
    reset();

    for (size_t i=0; i<rows; ++i) {
        data[i * cols + i] = 1.0f;
    }

    return this;
}

std::unique_ptr<Matrix> Matrix::copy() {
    return std::make_unique<Matrix>(*this);
}


const Matrix* Matrix::apply(const Matrix* a) {
    auto b = copy();

    for (size_t i=0; i<rows; ++i) {
        for (size_t j=0; j<cols; ++j) {
            data[i * 4 + j] = 0.0f;

            for (size_t k=0; k<rows; ++k) {
                data[i * 4 + j] += a->data[k * 4 + j] * b->data[i * 4 + k];
            }
        }
    }

    return this;
}

std::unique_ptr<Matrix> Matrix::perspective(float fovy, float aspect, float n, float f) {
    float b = 1.0f / tanf(fovy / 2.0f);
    float a = b / aspect;
    float c = -((f + n) / (f - n));
    float d = -((2.f * f * n) / (f - n));

    auto m = std::make_unique<Matrix>();

    size_t i =0;
    for (float v : {
            a, 0.0f, 0.0f, 0.0f,
            0.0f,    b, 0.0f, 0.0f,
            0.0f, 0.0f,    c, -1.0f,
            0.0f, 0.0f,    d, 0.0f,
    }) {
        m->data[i++] = v;
    }

    return m;
}

std::unique_ptr<Matrix> Matrix::inversedPerspective(float fovy, float aspect, float n, float f) {
    auto m = perspective(fovy, aspect, n, f);

    float a = m->data[0];
    float b = m->data[5];
    float c = m->data[10];
    float d = m->data[14];
    float e = m->data[11];

    m->data[0] = 1.0f / a;
    m->data[5] = 1.0f / b;
    m->data[11] = 1.0f / d;
    m->data[14] = 1.0f / e;
    m->data[15] = -c / (d*e);

    return m;
}


const Matrix* Matrix::translate(float x, float y, float z) {
    apply(Matrix::translation(x, y, z).get());
    return this;
}


const Matrix* Matrix::scale(float x, float y, float z) {
    apply(Matrix::scaling(x, y, z).get());
    return this;
}

const Matrix* Matrix::rotateX(float angle) {
    apply(Matrix::rotationX(angle).get());
    return this;
}

const Matrix* Matrix::rotateY(float angle) {
    apply(Matrix::rotationY(angle).get());
    return this;
}

const Matrix* Matrix::rotateZ(float angle) {
    apply(Matrix::rotationZ(angle).get());
    return this;
}

std::unique_ptr<Matrix> Matrix::translation(float x, float y, float z) {
    auto m = std::make_unique<Matrix>();

    m->data[12 + 0] = x;
    m->data[12 + 1] = y;
    m->data[12 + 2] = z;

    return m;
}

std::unique_ptr<Matrix> Matrix::scaling(float x, float y, float z) {
    auto m = std::make_unique<Matrix>();

    m->data[0]  = x;
    m->data[5]  = y;
    m->data[10] = z;

    return m;
}


std::unique_ptr<Matrix> Matrix::rotationX(float angle) {
    auto m = std::make_unique<Matrix>();

    float s = sinf(angle);
    float c = cosf(angle);

    m->data[5] = c;
    m->data[6] = s;
    m->data[9] = -s;
    m->data[10] = c;

    return m;
}


std::unique_ptr<Matrix> Matrix::rotationY(float angle) {
    auto m = std::make_unique<Matrix>();

    float s = sinf(angle);
    float c = cosf(angle);

    m->data[0] = c;
    m->data[2] = -s;
    m->data[8] = s;
    m->data[10] = c;

    return m;
}

std::unique_ptr<Matrix> Matrix::rotationZ(float angle) {
    auto m = std::make_unique<Matrix>();

    float s = sinf(angle);
    float c = cosf(angle);

    m->data[0] = c;
    m->data[1] = s;
    m->data[4] = -s;
    m->data[5] = c;

    return m;
}