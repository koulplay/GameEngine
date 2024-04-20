#include "GameEngineCore/camera.h"

#include "glm/trigonometric.hpp"


namespace game_engine {
Camera::Camera(const glm::vec3& position,
               const glm::vec3& rotation,
               const ProjectionMode projection_mode)
    : position_(position)
    , rotation_(rotation)
    , projection_mode_(projection_mode) {
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

void Camera::UpdateViewMatrix() {
    float rotate_in_radians_x = glm::radians(-rotation_.x);
    glm::mat4 rotate_matrix_x(1, 0, 0, 0,
                              0, cos(rotate_in_radians_x), sin(rotate_in_radians_x), 0,
                              0, -sin(rotate_in_radians_x), cos(rotate_in_radians_x), 0,
                              0, 0, 0, 1);

    float rotate_in_radians_y = glm::radians(-rotation_.y);
    glm::mat4 rotate_matrix_y(cos(rotate_in_radians_y), 0, -sin(rotate_in_radians_y), 0,
                              0, 1, 0, 0,
                              sin(rotate_in_radians_y), 0, cos(rotate_in_radians_y), 0,
                              0, 0, 0, 1);

    float rotate_in_radians_z = glm::radians(-rotation_.z);
    glm::mat4 rotate_matrix_z(cos(rotate_in_radians_z), sin(rotate_in_radians_z), 0, 0,
                              -sin(rotate_in_radians_z), cos(rotate_in_radians_z), 0, 0,
                              0, 0, 1, 0,
                              0, 0, 0, 1);

    glm::mat4 translate_matrix(1, 0, 0, 0,
                               0, 1, 0, 0,
                               0, 0, 1, 0,
                               -position_[0], -position_[1], -position_[2], 1);

    view_matrix = rotate_matrix_y * rotate_matrix_x * translate_matrix;
}

void Camera::UpdateProjectionMatrix() {
    if (projection_mode_ == ProjectionMode::PERSPECTIVE) {
        float r = 0.1f;
        float t = 0.1f;
        float f = 10;
        float n = 0.1f;
        projection_matrix_ = glm::mat4(n / r, 0, 0, 0,
                                       0, n / t, 0, 0,
                                       0, 0, (-f - n) / (f - n), -1,
                                       0, 0, -2 * f * n / (f - n), 0);
    }
    else {
        float r = 2;
        float t = 2;
        float f = 100;
        float n = 0.1f;
        projection_matrix_ = glm::mat4(1 / r, 0, 0, 0,
                                       0, 1 / t, 0, 0,
                                       0, 0, -2 / (f - n), 0,
                                       0, 0, (-f - n) / (f - n), 1);
    }
}

void Camera::SetPosition(const glm::vec3& position) {
    position_ = position;
    UpdateViewMatrix();
}

void Camera::SetRotation(const glm::vec3& rotation) {
    rotation_ = rotation;
    UpdateViewMatrix();
}

void Camera::SetPositionRotation(const glm::vec3& position, const glm::vec3& rotation) {
    position_ = position;
    rotation_ = rotation;
    UpdateViewMatrix();
}

void Camera::SetProjectionMode(const ProjectionMode projection_mode) {
    projection_mode_ = projection_mode;
    UpdateProjectionMatrix();
}
} // end namespace game_engine
