#include <GameEngineCore/window.h>
#include <GameEngineCore/log.h>
#include <GameEngineCore/windowEvent.h>
#include <GameEngineCore/mouseEvent.h>
#include <GameEngineCore/keyEvent.h>
#include "GameEngineCore/camera.h"

#include "GameEngineCore/Rendering/OpenGL/rendererOpenGL.h"
#include "GLFW/glfw3.h"

#include "Modules/UIModule.h"
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <utility>

namespace engine {

Window::Window(std::string title, const unsigned int wight, const unsigned int height)
    : data_({std::move(title), wight, height}) {
    int result_code = Init();
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

    glfwSetErrorCallback([](int error_code, const char* description) {
        LOG_CRITICAL("GLFW error: {0}", description);
    });

    if (!glfwInit()) {
        LOG_CRITICAL("[CORE] Can\'t initialize GLFW!");
        return -1;
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    /* Create a windowed mode window and its OpenGL context */
    p_window_ = glfwCreateWindow(data_.wight, data_.height, data_.title.c_str(), nullptr, nullptr);
    if (!p_window_) {
        LOG_CRITICAL("Can\'t create window '{0}' with size {1}x{2}", data_.title, data_.wight, data_.height);
        glfwTerminate();
        return -2;
    }

    if (!RendererOpenGL::Init(p_window_)) {
        LOG_CRITICAL("Failed to initialize OpenGL renderer");
        return -3;
    }

    glfwSetWindowUserPointer(p_window_, &this->data_);

    glfwSetKeyCallback(p_window_, [](GLFWwindow* p_window, int key, int scancode, int action, int mods) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_window));
        switch (action) {
            case GLFW_PRESS:
            {
                EventKeyPressed event(static_cast<KeyCode>(key), false);
                data.call_back_fn(event);
                break;
            }

            case GLFW_RELEASE:
            {
                EventKeyReleased event(static_cast<KeyCode>(key));
                data.call_back_fn(event);
                break;
            }

            case GLFW_REPEAT:
            {
                EventKeyPressed event(static_cast<KeyCode>(key), true);
                data.call_back_fn(event);
                break;
            }
            default:
                LOG_CRITICAL("Error glfwSetKeyCallback");
                break;
        }
    });

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
        RendererOpenGL::SetViewport(wight, height, 0, 0);
    });

    UIModule::OnWindowCreate(p_window_);

    return 0;
}

void Window::OnUpdate() {
    glfwSwapBuffers(p_window_);
    glfwPollEvents();
}

void Window::Shutdown() {
    UIModule::OnWindowClose();
    glfwDestroyWindow(p_window_);
    glfwTerminate();
}

} // end namespace engine
