#include <array>
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

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>

#include <SOIL2.h>

#include <glm/gtc/matrix_transform.hpp>

namespace engine {

// GLfloat positions_colors[]{
//     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
// };
// GLuint indices[] = {
//     0, 1, 3, // First Triangle
//     1, 2, 3  // Second Triangle
// };

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

const char* vertex_shader =
        R"(#version 460
        layout(location = 0) in vec3 vertex_pos;
        layout(location = 1) in vec3 normal_pos;

        out vec3 frag_pos;
        out vec3 frag_normal;

        uniform mat4 model;
        uniform mat4 viewProjection;

        void main() {
        	gl_Position = viewProjection * model * vec4(vertex_pos, 1.0);
            frag_pos = vec3(model * vec4(vertex_pos, 1.0f));
            frag_normal = normal_pos;
        })";

const char* fragment_shader =
        R"(#version 460
        in vec3 frag_pos;
        in vec3 frag_normal;

        out vec4 frag_color;

        struct Material {
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
            float shininess;
        };
        uniform Material material;

        struct Light {
            vec3 position;
            vec3 ambient;
            vec3 diffuse;
            vec3 specular;
        };
        uniform Light light;

        uniform vec3 objectColor;
        uniform vec3 lightColor;
        uniform vec3 lightPos;
        uniform vec3 viewPos;

        void main() {
            //ambient
            vec3 ambient = light.ambient * material.ambient;

            //diffuse
            vec3 norm = normalize(frag_normal);
            vec3 lightDir = normalize(light.position - frag_pos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = light.diffuse * (diff * material.diffuse);

            //specular
            vec3 viewDir = normalize(viewPos - frag_pos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
            vec3 specular = light.specular * (spec * material.specular);

            frag_color = vec4((diffuse + ambient + specular), 1.0f);
        })";

const char* light_vertex_shader =
        R"(#version 460
        layout(location = 0) in vec3 vertex_position;

        uniform mat4 model_matrix;
        uniform mat4 view_projection_matrix;

        void main() {
        	gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
        })";

const char* light_fragment_shader =
        R"(#version 460
        out vec4 frag_color;

        void main() {
            frag_color = vec4(1.0f);
        })";

std::array<glm::vec3, 5> positions = {
    glm::vec3(-2.f, -2.f, -4.f),
    glm::vec3(-5.f,  0.f,  3.f),
    glm::vec3( 2.f,  1.f, -2.f),
    glm::vec3( 4.f, -3.f,  3.f),
    glm::vec3( 1.f, -7.f,  1.f)
};

std::unique_ptr<ShaderProgram> p_shader_program;
std::unique_ptr<ShaderProgram> p_light_shader_program;
std::unique_ptr<VertexBuffer> p_vbo;
std::unique_ptr<IndexBuffer> p_index_buffer;
std::unique_ptr<VertexArray> p_vao;
std::unique_ptr<VertexArray> p_light_vao;
GLuint texture_buffer_1;
GLuint texture_buffer_2;

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
    if (!p_shader_program->IsCompiled()) { return -4; }

    p_light_shader_program = std::make_unique<ShaderProgram>(light_vertex_shader, light_fragment_shader);
    if (!p_light_shader_program->IsCompiled()) { return -4; }

    p_vao = std::make_unique<VertexArray>();

    BufferLayout buffer_layout{
        ShaderDataType::FLOAT3,
        ShaderDataType::FLOAT3,
    };

    p_vbo = std::make_unique<VertexBuffer>(vertices, sizeof(vertices),
                                                            buffer_layout);
    //p_index_buffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

    p_vao->AddVertexBuffer(*p_vbo);

    p_light_vao = std::make_unique<VertexArray>();
    p_light_vao->AddVertexBuffer(*p_vbo);

    //----------------------------------------------------//

    while (!close_window_) {
        RendererOpenGL::SetClearColor(background_color_[0], background_color_[1], background_color_[2], background_color_[3]);
        RendererOpenGL::Clear();

        p_shader_program->Bind();

        glm::mat4x4 scale_matrix(scale[0], 0, 0, 0,
                                 0, scale[1], 0, 0,
                                 0, 0, scale[2], 0,
                                 0, 0, 0, 1);

        const float rotate_in_radians = glm::radians(rotate);
        glm::mat4x4 rotate_matrix(cos(rotate_in_radians), sin(rotate_in_radians), 0, 0,
                                  -sin(rotate_in_radians), cos(rotate_in_radians), 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1);
        glm::mat4x4 translate_matrix(1, 0, 0, 0,
                                     0, 1, 0, 0,
                                     0, 0, 1, 0,
                                     translate[0], translate[1], translate[2], 1);

        glm::mat4x4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;

        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

        p_shader_program->SetUniform3f("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

        p_shader_program->SetUniform3f("material.ambient", glm::vec3( 1.0f, 0.5f, 0.31f));
        p_shader_program->SetUniform3f("material.diffuse", glm::vec3( 1.0f, 0.5f, 0.31f));
        p_shader_program->SetUniform3f("material.specular", glm::vec3( 0.5f, 0.5f, 0.5f));
        p_shader_program->SetUniform1f("material.shininess", 32.0f);

        p_shader_program->SetUniform3f("light.position", glm::vec3(lightPos));
        p_shader_program->SetUniform3f("light.ambient",  glm::vec3(0.2f, 0.2f, 0.2f));
        p_shader_program->SetUniform3f("light.diffuse",  glm::vec3(0.5f, 0.5f, 0.5f));
        p_shader_program->SetUniform3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

        p_shader_program->SetUniform3f("viewPos", camera.GetPosition());

        camera.SetProjectionMode(perspective_camera
                                 ? Camera::ProjectionMode::PERSPECTIVE
                                 : Camera::ProjectionMode::ORTHOGRAPHIC);

        p_shader_program->SetUniformMatrix4("model", model_matrix);
        p_shader_program->SetUniformMatrix4("viewProjection", camera.GetProjectionMatrix() * camera.GetViewMatrix());

        RendererOpenGL::DrawArrays(*p_vao, 36);

        p_light_shader_program->Bind();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);

        model = glm::scale(model, glm::vec3(0.2f));
        p_light_shader_program->SetUniformMatrix4("model_matrix", model);
        p_light_shader_program->SetUniformMatrix4("view_projection_matrix", camera.GetProjectionMatrix() * camera.GetViewMatrix());

        RendererOpenGL::DrawArrays(*p_light_vao, 36);
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
