#include <array>
#include <GameEngineCore/application.h>
#include <GameEngineCore/log.h>
#include <GameEngineCore/window.h>
#include <GameEngineCore/input.h>
#include "GameEngineCore/texture.h"

#include "GameEngineCore/Rendering/OpenGL/rendererOpenGL.h"
#include "Rendering/OpenGL/shaderProgram.h"
#include "Rendering/OpenGL/vertexBuffer.h"
#include "Rendering/OpenGL/indexBuffer.h"
#include "Rendering/OpenGL/vertexArray.h"

#include <imgui/imgui.h>
#include "Modules/UIModule.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL2.h>

namespace engine {

float vertices[] = {
     // positions         // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 positions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

std::unique_ptr<ShaderProgram> p_shader_program;
std::unique_ptr<ShaderProgram> p_light_shader_program;
std::unique_ptr<VertexBuffer> p_vbo;
std::unique_ptr<IndexBuffer> p_index_buffer;
std::unique_ptr<VertexArray> p_vao;
std::unique_ptr<VertexArray> p_light_vao;
std::unique_ptr<Texture> p_container_diffuse_map;
std::unique_ptr<Texture> p_container_specular_map;
GLuint container_diffuse_map;
GLuint container_specular_map;

float scale[3]{1.f, 1.f, 1.f};
float rotate = 0.f;
float translate[3]{0.f, 0.f, 0.f};
float background_color_[4]{0.33f, 0.33f, 0.33f, 0.f};

Application::Application() {
    LOG_INFO("[CORE] Starting Application");
}

Application::~Application() {
    LOG_INFO("[CORE] Closing Application");
}

void Application::OnEvent(EventBase& event) {
    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<EventWindowClose>([this](EventWindowClose& event) {
        LOG_INFO("[CORE] [EVENT] Window Close");
        close_window_ = true;
    });

    dispatcher.Dispatch<EventKeyPressed>([this](EventKeyPressed& event) {
        if (event.GetKeyButton() <= KeyCode::KEY_Z) {
            if (event.isRepeated()) {
                LOG_INFO("[CORE] [EVENT] Key pressed and repeated: {0}", static_cast<char>(event.GetKeyButton()));
            }
            else {
                LOG_INFO("[CORE] [EVENT] Key pressed: {0}", static_cast<char>(event.GetKeyButton()));
            }
        }
        Input::PressKey(event.GetKeyButton());
    });

    dispatcher.Dispatch<EventKeyReleased>([this](EventKeyReleased& event) {
        if (event.GetKeyButton() <= KeyCode::KEY_Z) {
            LOG_INFO("[CORE] [EVENT] Key released: {0}", static_cast<char>(event.GetKeyButton()));
        }
        Input::ReleaseKey(event.GetKeyButton());
    });

    dispatcher.Dispatch<EventWindowResize>([this](EventWindowResize& event) {
        //LOG_INFO("[CORE] [EVENT] Changed size to {0}x{1}", event.GetWidth(), event.GetHeight());
    });

    dispatcher.Dispatch<EventMouseMoved>([this](EventMouseMoved& event) {
        //LOG_INFO("[CORE] [EVENT] Mouse moved to {0}x{1}", event.GetMouseX(), event.GetMouseY());
    });
}

bool Application::OnWindowClose(EventWindowClose& event) {
    close_window_ = true;
    this->~Application();
    return true;
}

int Application::Start(unsigned int window_width, unsigned int window_height, const char* title) {
    p_window_ = std::make_unique<Window>(title, window_width, window_height);
    p_window_->SetEventCallback([this](EventBase& event) { this->OnEvent(event); });

    //----------------------------------------------------//
    p_shader_program = std::make_unique<ShaderProgram>(R"(C:\dev\repos\CLion\GameEngine\GameEngine\GameEngineCore\src\GameEngineCore\Shaders\cube.vert)",
                                                     R"(C:\dev\repos\CLion\GameEngine\GameEngine\GameEngineCore\src\GameEngineCore\Shaders\cube.frag)");
    if (!p_shader_program->IsCompiled()) { return -4; }

    p_light_shader_program = std::make_unique<ShaderProgram>(R"(C:\dev\repos\CLion\GameEngine\GameEngine\GameEngineCore\src\GameEngineCore\Shaders\light.vert)",
                                                           R"(C:\dev\repos\CLion\GameEngine\GameEngine\GameEngineCore\src\GameEngineCore\Shaders\light.frag)");
    if (!p_light_shader_program->IsCompiled()) { return -4; }

    p_vao = std::make_unique<VertexArray>();

    BufferLayout buffer_layout{
        ShaderDataType::FLOAT3,
        ShaderDataType::FLOAT3,
        ShaderDataType::FLOAT2,
    };

    p_vbo = std::make_unique<VertexBuffer>(vertices, sizeof(vertices),
                                                            buffer_layout);
    //p_index_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

    p_vao->AddVertexBuffer(*p_vbo);

    p_light_vao = std::make_unique<VertexArray>();
    p_light_vao->AddVertexBuffer(*p_vbo);


    p_container_diffuse_map = std::make_unique<Texture>(R"(C:\dev\repos\CLion\GameEngine\GameEngine\GameEngineCore\src\container2.png)");

    p_container_specular_map = std::make_unique<Texture>(R"(C:\dev\repos\CLion\GameEngine\GameEngine\GameEngineCore\src\container2_specular.png)");

    //----------------------------------------------------//

    while (!close_window_) {
        RendererOpenGL::SetClearColor(background_color_[0], background_color_[1], background_color_[2], background_color_[3]);
        RendererOpenGL::Clear();

        p_shader_program->Bind();

        p_container_diffuse_map->SetActiveTexture(GL_TEXTURE0);
        p_shader_program->SetUniform1i("material.diffuse", 0);

        p_container_specular_map->SetActiveTexture(GL_TEXTURE1);
        p_shader_program->SetUniform1i("material.specular", 1);

        p_shader_program->SetUniform1f("material.shininess", 32.0f);

        p_shader_program->SetUniform3fv("view_pos", camera.GetPosition());

        p_shader_program->SetUniform3fv("dir_light.direction", glm::vec3(0.0f, -1.0f, 0.0f));
        p_shader_program->SetUniform3fv("dir_light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        p_shader_program->SetUniform3fv("dir_light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        p_shader_program->SetUniform3fv("dir_light.specular", glm::vec3(0.5f, 0.5f, 0.5f));

        //glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        std::vector<glm::vec3> pointLightPositions {
            glm::vec3( 0.7f,  0.2f,  2.0f),
            glm::vec3( 2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3( 0.0f,  0.0f, -3.0f)
        };

        for (int i = 0; i < pointLightPositions.size(); ++i) {
            auto index = std::to_string(i);
            p_shader_program->SetUniform3fv(("point_lights[" + index + "].position").c_str(), pointLightPositions[i]);
            p_shader_program->SetUniform3fv(("point_lights[" + index + "].ambient").c_str(), glm::vec3(0.1f));
            p_shader_program->SetUniform3fv(("point_lights[" + index + "].diffuse").c_str(), glm::vec3(0.6f));
            p_shader_program->SetUniform3fv(("point_lights[" + index + "].specular").c_str(), glm::vec3(1.0f));
            p_shader_program->SetUniform1f(("point_lights[" + index + "].constant").c_str(), 1.0f);
            p_shader_program->SetUniform1f(("point_lights[" + index + "].linear").c_str(), 0.09);
            p_shader_program->SetUniform1f(("point_lights[" + index + "].quadratic").c_str(), 0.032);
        }

        p_shader_program->SetUniform3fv("spec_light.position", camera.GetPosition());
        p_shader_program->SetUniform3fv("spec_light.direction", camera.GetDirection());
        p_shader_program->SetUniform3fv("spec_light.ambient", glm::vec3(0.1f));
        p_shader_program->SetUniform3fv("spec_light.diffuse", glm::vec3(0.6f));
        p_shader_program->SetUniform3fv("spec_light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        p_shader_program->SetUniform1f("spec_light.cut_off", glm::cos(glm::radians(12.5f)));
        p_shader_program->SetUniform1f("spec_light.outer_cut_off", glm::cos(glm::radians(15.5f)));

        camera.SetProjectionMode(perspective_camera
                                 ? Camera::ProjectionMode::PERSPECTIVE
                                 : Camera::ProjectionMode::ORTHOGRAPHIC);

        p_shader_program->SetUniformMatrix4("view", camera.GetViewMatrix());
        p_shader_program->SetUniformMatrix4("projection", camera.GetProjectionMatrix());

        for(unsigned int i = 0; i < 10; i++) {
            glm::mat4 model(1.);
            float angle = 20.0f * i;
            model = glm::translate(model, positions[i]);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            p_shader_program->SetUniformMatrix4("model", model);

            RendererOpenGL::DrawArrays(*p_vao, 36);
        }

        p_light_shader_program->Bind();

        p_light_shader_program->SetUniformMatrix4("view_projection_matrix", camera.GetProjectionMatrix() * camera.GetViewMatrix());
        for (int i = 0; i < pointLightPositions.size(); ++i) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            p_light_shader_program->SetUniformMatrix4("model_matrix", model);

            RendererOpenGL::DrawArrays(*p_light_vao, 36);
        }

        glBindVertexArray(0);

        //----------------------------------------------------//
        UIModule::OnUIDrawBegin();
        bool show = true;
        UIModule::ShowExampleAppDockSpace(&show);
        ImGui::ShowDemoWindow();

        ImGui::Begin("Background Color Window");
        ImGui::ColorEdit4("Background Color", background_color_);
        ImGui::SliderFloat3("scale", scale, 0.f, 2.0f);
        ImGui::SliderFloat("rotate", &rotate, -360.0f, 360.0f);
        ImGui::SliderFloat3("translate", translate, -10.f, 10.0f);

        ImGui::Checkbox("Perspective camera", &perspective_camera);
        ImGui::End();
        //----------------------------------------------------//
        OnUIDraw();

        UIModule::OnUIDrawEnd();

        p_window_->OnUpdate();
        this->OnUpdate();
    }
    p_window_ = nullptr;
    glfwTerminate();
    return 0;

}

} // end namespace engine
