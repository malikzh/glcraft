//
// Created by malikzh on 26.06.2022.
//
#include <initializer_list>

#ifndef GLCRAFT_MATRIX_HPP
#define GLCRAFT_MATRIX_HPP


/**
 * Данные внутри класса матрицы представлюят из себя column-major формат,
 * т.е мы храним транспонированную матрицу
 */
class Matrix {
public:
    static constexpr unsigned int rows = 4;
    static constexpr unsigned int cols = 4;
    static constexpr unsigned int size = rows*cols;

    float data[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f,
                      0.0f, 0.0f, 0.0f, 1.0f,
                      };

    Matrix() = default;
    Matrix(const std::initializer_list<float>& values);
    Matrix(const Matrix& matrix);

    const Matrix* reset();
    const Matrix* identity();
    std::unique_ptr<Matrix> copy();

    const Matrix* apply(const Matrix* a);

    // Проекция
    static std::unique_ptr<Matrix> perspective(float fovy, float aspect, float n, float f);

    // Трансформации
    const Matrix* translate(float x, float y, float z);
    const Matrix* scale(float x, float y, float z);
    const Matrix* rotateX(float angle);
    const Matrix* rotateY(float angle);
    const Matrix* rotateZ(float angle);

    static std::unique_ptr<Matrix> translation(float x, float y, float z);
    static std::unique_ptr<Matrix> scaling(float x, float y, float z);
    static std::unique_ptr<Matrix> rotationX(float angle);
    static std::unique_ptr<Matrix> rotationY(float angle);
    static std::unique_ptr<Matrix> rotationZ(float angle);


};


#endif //GLCRAFT_MATRIX_HPP
