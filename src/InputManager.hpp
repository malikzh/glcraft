//
// Created by malikzh on 26.06.2022.
//

#ifndef GLCRAFT_INPUTMANAGER_HPP
#define GLCRAFT_INPUTMANAGER_HPP


class InputManager {
public:
    float mouseX = 0.0f;
    float mouseY = 0.0f;
    float mouseDX = 0.0f;
    float mouseDY = 0.0f;

    bool forwardKeyPressed  = false;
    bool backwardKeyPressed = false;
    bool leftKeyPressed     = false;
    bool rightKeyPressed    = false;
    bool spaceKeyPressed    = false;
    bool shiftKeyPressed    = false;
};


#endif //GLCRAFT_INPUTMANAGER_HPP
