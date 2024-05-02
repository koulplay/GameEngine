#include <GameEngineCore/application.h>
#include <GameEngineCore/input.h>
#include <GameEngineCore/camera.h>

#include <iostream>
#include <memory>

#include "imgui.h"

class EngineEditor : public engine::Application {
    void OnUpdate() override {
        glm::vec3 movement_delta{0, 0, 0};
        glm::vec3 rotation_delta{0, 0, 0};

        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_W)) {
            movement_delta.z -= 0.05f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_S)) {
            movement_delta.z += 0.05f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_A)) {
            movement_delta.x -= 0.05f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_D)) {
            movement_delta.x += 0.05f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_E)) {
            movement_delta.y += 0.01f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_Q)) {
            movement_delta.y -= 0.01f;
        }

        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_UP)) {
            rotation_delta.x += 1.5f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_DOWN)) {
            rotation_delta.x -= 1.5f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_RIGHT)) {
            rotation_delta.y -= 1.5f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_LEFT)) {
            rotation_delta.y += 1.5f;
        }

        camera.SetPositionAndRotationDelta(movement_delta, rotation_delta);
    }

    void OnUIDraw() override {
        ImGui::Begin("Editor");
        ImGui::SliderFloat3("camera position", camera_position, -10.f, 10.0f);
        ImGui::SliderFloat3("camera rotation", camera_rotation, 0.f, 360.0f);
        ImGui::Checkbox("Perspective camera", &perspective_camera);
        ImGui::End();
    }

    int frame = 0;
};

int main() {
    std::cout << "GameEngineEditor" << std::endl;
    std::unique_ptr<EngineEditor> engine_editor = std::make_unique<EngineEditor>();

    int return_code = engine_editor->Start(1024, 768, "EngineEditor");

    std::cin.get();

    return return_code;
}
