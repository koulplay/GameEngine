#include <GameEngineCore/window.h>
#include <GameEngineCore/log.h>
#include <GameEngineCore/windowEvent.h>
#include <GameEngineCore/mouseEvent.h>
#include <GameEngineCore/keyEvent.h>
#include "Rendering/OpenGL/shaderProgram.h"
#include "Rendering/OpenGL/vertexBuffer.h"
#include "Rendering/OpenGL/indexBuffer.h"
#include "Rendering/OpenGL/vertexArray.h"
#include "GameEngineCore/camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utility>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>


namespace game_engine {
static bool is_GLFW_initialized = false;

GLfloat positions_colors[]{
    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
};

GLuint indices[]{
    0, 1, 2,
    3, 2, 1
};

const GLchar* vertex_shader =
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

const GLchar* fragment_shader =
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

float camera_position[3]{0.0f, 0.0f, 1.0f};
float camera_rotation[3]{0.0f, 0.0f, 0.0f};
bool perspective_camera = false;
Camera camera;


Window::Window(std::string title, const unsigned int wight, const unsigned int height)
    : data_({std::move(title), wight, height}) {
    int result_code = Init();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplOpenGL3_Init();
    ImGui_ImplGlfw_InitForOpenGL(p_window_, true);
}

Window::~Window() {
    Shutdown();
}

unsigned int Window::GetWight() const { return data_.wight; }

unsigned int Window::GetHeight() const { return data_.height; }

void Window::SetEventCallback(const EventCallbackFn& callback) {
    data_.call_back_fn = callback;
}

int Window::Init() {
    LOG_INFO("[CORE] Creating window '{0}' with size {1}x{2}", data_.title, data_.wight, data_.height);

    /* Initialize the library */
    if (!is_GLFW_initialized) {
        if (!glfwInit()) {
            LOG_CRITICAL("[CORE] Can\'t initialize GLFW!");
            return -1;
        }

        is_GLFW_initialized = true;
    }

    /* Create a windowed mode window and its OpenGL context */
    p_window_ = glfwCreateWindow(data_.wight, data_.height, data_.title.c_str(), nullptr, nullptr);
    if (!p_window_) {
        LOG_CRITICAL("[CORE] Can\'t create window '{0}' with size {1}x{2}", data_.title, data_.wight, data_.height);
        glfwTerminate();
        return -2;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(p_window_);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        LOG_CRITICAL("[CORE] Failed to initialize GLAD");
        return -3;
    }

    glfwSetWindowUserPointer(p_window_, &this->data_);

    glfwSetWindowSizeCallback(p_window_, [](GLFWwindow* p_window, int wight, int height) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_window));
        data.wight = wight;
        data.height = height;

        EventWindowResize event(wight, height);
        data.call_back_fn(event);
    });

    glfwSetCursorPosCallback(p_window_, [](GLFWwindow* p_window, double mouseX, double mouseY) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_window));

        EventMouseMoved event(mouseX, mouseY);
        data.call_back_fn(event);
    });

    glfwSetWindowCloseCallback(p_window_, [](GLFWwindow* p_window) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_window));

        EventWindowClose event;
        data.call_back_fn(event);
    });

    glfwSetFramebufferSizeCallback(p_window_, [](GLFWwindow* p_window, int wight, int height) {
        glViewport(0, 0, wight, height);
    });


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

    glm::mat3 mat_1(4, 0, 0, 2, 8, 1, 0, 1, 0);
    glm::mat3 mat_2(4, 2, 9, 2, 0, 4, 1, 4, 2);

    glm::mat3 result_mat = mat_1 * mat_2;

    LOG_INFO("");
    LOG_INFO("|{0:3} {1:3} {2:3}|", result_mat[0][0], result_mat[1][0], result_mat[2][0]);
    LOG_INFO("|{0:3} {1:3} {2:3}|", result_mat[0][1], result_mat[1][1], result_mat[2][1]);
    LOG_INFO("|{0:3} {1:3} {2:3}|", result_mat[0][2], result_mat[1][2], result_mat[2][2]);
    LOG_INFO("");

    glm::vec4 vec(1, 2, 3, 4);
    glm::mat4 mat_identity(1);

    glm::vec4 result_vec = mat_identity * vec;
    LOG_INFO("({0} {1} {2} {3})", result_vec[0], result_vec[1], result_vec[2], result_vec[3]);

    return 0;
}

void Window::OnUpdate() {
    glClearColor(background_color_[0], background_color_[1], background_color_[2], background_color_[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = static_cast<float>(data_.wight);
    io.DisplaySize.y = static_cast<float>(data_.height);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui::ShowDemoWindow();

    ImGui::Begin("Background Color Window");
    ImGui::ColorEdit4("Background Color", background_color_);
    ImGui::SliderFloat3("scale", scale, 0.f, 2.0f);
    ImGui::SliderFloat("rotate", &rotate, 0.f, 360.0f);
    ImGui::SliderFloat3("translate", translate, -1.f, 1.0f);

    ImGui::SliderFloat3("camera position", camera_position, -10.f, 10.0f);
    ImGui::SliderFloat3("camera rotation", camera_rotation, 0.f, 360.0f);
    ImGui::Checkbox("Perspective camera", &perspective_camera);
    ImGui::End();

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

    camera.SetPositionRotation(glm::vec3(camera_position[0], camera_position[1], camera_position[2]),
                               glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
    camera.SetProjectionMode(perspective_camera
                             ? Camera::ProjectionMode::PERSPECTIVE
                             : Camera::ProjectionMode::ORTHOGRAPHIC);

    p_shader_program->SetMatrix4("view_projection_matrix", camera.GetProjectionMatrix() * camera.GetViewMatrix());

    p_vao->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(p_vao->GetIndecesCount()), GL_UNSIGNED_INT, nullptr);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    glfwSwapBuffers(p_window_);
    glfwPollEvents();
}

void Window::Shutdown() {
    glfwDestroyWindow(p_window_);
    glfwTerminate();
}
} // end namespace game_engine
