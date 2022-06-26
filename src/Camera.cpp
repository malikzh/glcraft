#include "glcraft.hpp"

void Camera::rotateY(float angle) {
    look.y += angle;
}

void Camera::rotateX(float angle) {
    look.x += angle;
}

void Camera::move(float x, float y, float z) {
    position.x += x;
    position.y += y;
    position.z += z;
}

void Camera::setPOV(Matrix* matrix) {
    matrix->translate(position.x, position.y, position.z);
    matrix->rotateY(look.y);
    matrix->rotateX(look.x);
}


void Camera::handleInput() {
    if (inman->leftKeyPressed) {
        move(0.01f, 0.0f, 0.0f);
    }

    if (inman->rightKeyPressed) {
        move(-0.01f, 0.0f, 0.0f);
    }

    if (inman->forwardKeyPressed) {
        move(0.0f, 0.0f, 0.01f);
    }

    if (inman->backwardKeyPressed) {
        move(0.0f, 0.0f, -0.01f);
    }

    rotateY(inman->mouseDX / 10.0f);
    rotateX(inman->mouseDY / 10.0f);
}