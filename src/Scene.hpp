//
// Created by malikzh on 11.06.2022.
//

#ifndef GLCRAFT_SCENE_HPP
#define GLCRAFT_SCENE_HPP


class Scene {
public:
    std::unique_ptr<Matrix> projectionMatrix;
    std::unique_ptr<Matrix> inversedProjectionMatrix;

    Scene();
    void render();
    void updateProjectionMatrix(float aspect);

    static std::unique_ptr<Matrix> createProjectionMatrix(float aspect);
    static std::unique_ptr<Matrix> createInversedProjectionMatrix(float aspect);
};


#endif //GLCRAFT_SCENE_HPP
