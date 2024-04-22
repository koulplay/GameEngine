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

    [[nodiscard]] glm::mat4 GetViewMatrix() const { return view_matrix; }
    [[nodiscard]] glm::mat4 GetProjectionMatrix() const { return projection_matrix_; }

private:
    void UpdateViewMatrix();
    void UpdateProjectionMatrix();

    glm::vec3 position_;
    glm::vec3 rotation_;
    ProjectionMode projection_mode_;
    glm::mat4 view_matrix;
    glm::mat4 projection_matrix_;
};
} // end namespace engine
