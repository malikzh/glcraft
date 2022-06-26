//
// Created by malikzh on 26.06.2022.
//

#ifndef GLCRAFT_CAMERA_HPP
#define GLCRAFT_CAMERA_HPP


class Camera {
public:
    const float speed = 0.05f;

    Vector up   = Vector(0.0f, 1.0f, 0.0f); // верх камеры
    Vector look = Vector(0.0f, 0.0f, 0.0f); // углы направления взгляда
    Vector position  = Vector(0.0f, 0.0f, 5.0f); // где находится камера в пространстве

    void rotateY(float angle);
    void rotateX(float angle);
    void move(float x, float y, float z);
    void setPOV(Matrix* matrix);
    void handleInput();
};


#endif //GLCRAFT_CAMERA_HPP
