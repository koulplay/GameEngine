#include <GameEngineCore/application.h>

#include <iostream>
#include <memory>

#include "imgui.h"

class EngineEditor : public engine::Application {
    void OnUpdate() override {
        //std::cout << "Update frame: " << frame++ << std::endl;
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
