#include <cmath>
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
    matrix->translate(-position.x, -position.y, -position.z);
    matrix->rotateY(-look.y);
    matrix->rotateX(-look.x);
}


void Camera::handleInput() {
    rotateY(-inman->mouseDX / 50.0f);
    rotateX(-inman->mouseDY / 50.0f);

    Vector movementVector(sin(look.y), 0.0f, cos(look.y));


    auto sideVector = movementVector.cross(&up);
    sideVector->norm();

    sideVector->scale(speed);
    movementVector.scale(speed);

    if (inman->leftKeyPressed) {
        position.add(sideVector.get());
    }

    if (inman->rightKeyPressed) {
        position.add(sideVector->invert());
    }

    if (inman->forwardKeyPressed) {
        position.add(movementVector.invert());
    }

    if (inman->backwardKeyPressed) {
        position.add(&movementVector);
    }

    if (inman->spaceKeyPressed) {
        position.y += speed;
    }

    if (inman->shiftKeyPressed) {
        position.y -= speed;
    }
}