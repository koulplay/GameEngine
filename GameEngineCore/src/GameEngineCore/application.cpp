#include <GameEngineCore/application.h>
#include <GameEngineCore/log.h>
#include <GameEngineCore/window.h>
#include <GameEngineCore/input.h>

#include "GameEngineCore/Rendering/OpenGL/rendererOpenGL.h"
#include "Rendering/OpenGL/shaderProgram.h"
#include "Rendering/OpenGL/vertexBuffer.h"
#include "Rendering/OpenGL/indexBuffer.h"
#include "Rendering/OpenGL/vertexArray.h"

#include <imgui/imgui.h>
#include "Modules/UIModule.h"

#include <GLFW/glfw3.h>

#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>

namespace engine {

// GLfloat positions_colors[]{
//     -0.5f, -0.5f,  0.0f,  1.0f,  1.0f,  0.0f,
//      0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  1.0f,
//     -0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,
//      0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.0f,
// };

GLfloat positions_colors[] = {
    -0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,

    -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,

    -0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  1.0f
};

GLuint indices[]{
    0, 1, 2,
    3, 2, 1
};

const char* vertex_shader =
        R"(#version 460
        layout(location = 0) in vec3 vertex_position;
        layout(location = 1) in vec3 vertex_color;
        uniform mat4 model_matrix;
        uniform mat4 view_projection_matrix;
        out vec3 color;
        void main() {
            color = vertex_color;
        	gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
        })";

const char* fragment_shader =
        R"(#version 460
        in vec3 color;
        out vec4 frag_color;
        void main() {
            frag_color = vec4(color, 1.0);
        })";

std::unique_ptr<ShaderProgram> p_shader_program;
std::unique_ptr<VertexBuffer> p_positions_colors_vbo;
std::unique_ptr<IndexBuffer> p_index_buffer;
std::unique_ptr<VertexArray> p_vao;
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
    p_shader_program = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);
    if (!p_shader_program->IsCompiled()) { return false; }

    BufferLayout buffer_layout_2vec3{
        ShaderDataType::FLOAT3,
        ShaderDataType::FLOAT3
    };

    p_vao = std::make_unique<VertexArray>();
    p_positions_colors_vbo = std::make_unique<VertexBuffer>(positions_colors, sizeof(positions_colors),
                                                            buffer_layout_2vec3);
    p_index_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

    p_vao->AddVertexBuffer(*p_positions_colors_vbo);
    p_vao->AddIndexBuffer(*p_index_buffer);


    //----------------------------------------------------//

    while (!close_window_) {
        RendererOpenGL::SetClearColor(background_color_[0], background_color_[1], background_color_[2],
                                      background_color_[3]);
        RendererOpenGL::Clear();

        p_shader_program->Bind();

        glm::mat4x4 scale_matrix(scale[0], 0, 0, 0,
                                 0, scale[1], 0, 0,
                                 0, 0, scale[2], 0,
                                 0, 0, 0, 1);

        float rotate_in_radians = glm::radians(rotate);
        glm::mat4x4 rotate_matrix(cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
                                  -sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1);

        glm::mat4x4 translate_matrix(1, 0, 0, 0,
                                     0, 1, 0, 0,
                                     0, 0, 1, 0,
                                     translate[0], translate[1], translate[2], 1);

        glm::mat4x4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;
        p_shader_program->SetMatrix4("model_matrix", model_matrix);


        camera.SetProjectionMode(perspective_camera
                                 ? Camera::ProjectionMode::PERSPECTIVE
                                 : Camera::ProjectionMode::ORTHOGRAPHIC);

        p_shader_program->SetMatrix4("view_projection_matrix", camera.GetProjectionMatrix() * camera.GetViewMatrix());

        RendererOpenGL::Draw(*p_vao);

        //----------------------------------------------------//
        UIModule::OnUIDrawBegin();
        bool show = true;
        UIModule::ShowExampleAppDockSpace(&show);
        ImGui::ShowDemoWindow();

        ImGui::Begin("Background Color Window");
        ImGui::ColorEdit4("Background Color", background_color_);
        ImGui::SliderFloat3("scale", scale, 0.f, 2.0f);
        ImGui::SliderFloat("rotate", &rotate, 0.f, 360.0f);
        ImGui::SliderFloat3("translate", translate, -10.f, 10.0f);

        ImGui::SliderFloat3("camera position", camera_position, -10.f, 10.0f);
        ImGui::SliderFloat3("camera rotation", camera_rotation, 0.f, 360.0f);
        ImGui::Checkbox("Perspective camera", &perspective_camera);
        ImGui::End();
        //----------------------------------------------------//
        OnUIDraw();

        UIModule::OnUIDrawEnd();

        p_window_->OnUpdate();
        this->OnUpdate();
    }
    p_window_ = nullptr;
    return 0;
}

} // end namespace engine
