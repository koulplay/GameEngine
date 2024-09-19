#pragma once

#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

namespace engine {

class Camera {
public:
    enum class ProjectionMode {
        PERSPECTIVE,
        ORTHOGRAPHIC,
    };

    Camera() = default;

    Camera(const glm::vec3& position,
           const glm::vec3& rotation,
           const ProjectionMode projection_mode);

    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    void SetPositionRotation(const glm::vec3& position, const glm::vec3& rotation);
    void SetProjectionMode(const ProjectionMode projection_mode);

    [[nodiscard]] glm::mat4 GetViewMatrix() const { return view_matrix_; }
    [[nodiscard]] glm::mat4 GetProjectionMatrix() const { return projection_matrix_; }
    [[nodiscard]] glm::vec3 GetPosition() const { return position_; }

    void MoveForward(const float delta);
    void MoveRight(const float delta);
    void MoveUp(const float delta);

    void SetPositionAndRotationDelta(const glm::vec3 movement_delta, const glm::vec3 rotation_delta);

private:
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

    glm::vec3 position_{0.0f, 0.0f, 3.0f};
    glm::vec3 rotation_;
    ProjectionMode projection_mode_;

    glm::vec3 direction_;
    glm::vec3 right_;
    glm::vec3 up_;

    static constexpr glm::vec3 world_direction_{0.0f, 0.0f, -1.0f};
    static constexpr glm::vec3 world_right_{-1.0f, 0.0f, 0.0f};
    static constexpr glm::vec3 world_up_{0.0f, 1.0f, 0.0f};

    glm::mat4 view_matrix_;
    glm::mat4 projection_matrix_;
};

} // end namespace engine
