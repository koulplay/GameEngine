#include <GameEngineCore/application.h>
#include <GameEngineCore/input.h>

#include <iostream>
#include <memory>

#include "imgui.h"

class EngineEditor : public engine::Application {
    void OnUpdate() override {
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_W)) {
            camera_position[2] -= 0.01f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_S)) {
            camera_position[2] += 0.01f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_A)) {
            camera_position[0] -= 0.01f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_D)) {
            camera_position[0] += 0.01f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_E)) {
            camera_position[1] += 0.01f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_Q)) {
            camera_position[1] -= 0.01f;
        }

        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_UP)) {
            camera_rotation[0] += 0.5f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_DOWN)) {
            camera_rotation[0] -= 0.5f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_RIGHT)) {
            camera_rotation[1] -= 0.5f;
        }
        if (engine::Input::isKeyPressed(engine::KeyCode::KEY_LEFT)) {
            camera_rotation[1] += 0.5f;
        }
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
