#include "GameEngineCore/camera.h"

#include "glm/trigonometric.hpp"
#include "glm/ext/matrix_transform.hpp"

namespace engine {

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
    float rotate_in_radians_y = glm::radians(-rotation_.y);
    float rotate_in_radians_z = glm::radians(-rotation_.z);

    const glm::mat3 rotate_matrix_x(1, 0, 0,
                              0, cos(rotate_in_radians_x), sin(rotate_in_radians_x),
                              0, -sin(rotate_in_radians_x), cos(rotate_in_radians_x));

    const glm::mat3 rotate_matrix_y(cos(rotate_in_radians_y), 0, -sin(rotate_in_radians_y),
                              0, 1, 0,
                              sin(rotate_in_radians_y), 0, cos(rotate_in_radians_y));

    const glm::mat3 rotate_matrix_z(cos(rotate_in_radians_z), sin(rotate_in_radians_z), 0,
                              -sin(rotate_in_radians_z), cos(rotate_in_radians_z), 0,
                              0, 0, 1);

    const glm::mat3 euler_rotate_matrix = rotate_matrix_z * rotate_matrix_y * rotate_matrix_x;

    direction_ = glm::normalize(euler_rotate_matrix * world_direction_);
    right_ = glm::normalize(euler_rotate_matrix * world_right_);
    up_ = glm::cross(direction_, right_);

    view_matrix_ = glm::lookAt(position_, position_ + direction_, up_);

}

void Camera::UpdateProjectionMatrix() {
    if (projection_mode_ == ProjectionMode::PERSPECTIVE) {
        float r = 0.1f;
        float t = 0.1f;
        float f = 100;
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
                                       0, 0, (-f - n) / (f - n), 0);
    }
}

void Camera::SetPositionAndRotationDelta(const glm::vec3 movement_delta, const glm::vec3 rotation_delta) {
    position_ -= direction_ * movement_delta.z;
    position_ -= right_ * movement_delta.x;
    position_ += up_ * movement_delta.y;
    rotation_ -= rotation_delta;
    UpdateViewMatrix();
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

void Camera::MoveForward(const float delta) {
    position_ += direction_ * delta;
    UpdateViewMatrix();
}

void Camera::MoveRight(const float delta) {
    position_ += right_ * delta;
    UpdateViewMatrix();
}

void Camera::MoveUp(const float delta) {
    position_ += up_ * delta;
    UpdateViewMatrix();
}

} // end namespace engine
