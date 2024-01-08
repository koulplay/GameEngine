#include <GameEngineCore/window.h>
#include <GameEngineCore/log.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utility>

namespace game_engine {

static bool is_GLFW_initialized = false;

Window::Window(std::string title, const unsigned int wight, const unsigned int height)
	: data_({ std::move(title), wight, height }) {
	int result_code = Init();
}

Window::~Window() {

}

unsigned int Window::GetWight() const { return data_.wight; }

unsigned int Window::GetHeight() const { return data_.height; }

void Window::SetEventCallback(const EventCallbackFn& callback) {
	data_.call_back_fn = callback;
}

void Window::OnUpdate() {
	glClearColor(1, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(p_window_);
	glfwPollEvents();
}

int Window::Init() {
	LOG_INFO("Creating window '{0}' with size {1}x{2}", data_.title, data_.wight, data_.height);

	/* Initialize the library */
	if (!is_GLFW_initialized){
		if(!glfwInit()){
			LOG_CRITICAL("Can\'t initialize GLFW!");
			return -1;
		}
			
		is_GLFW_initialized = true;
	}

	/* Create a windowed mode window and its OpenGL context */
	p_window_ = glfwCreateWindow(data_.wight, data_.height, data_.title.c_str(), nullptr, nullptr);
	if(!p_window_) {
		LOG_CRITICAL("Can\'t create window '{0}' with size {1}x{2}", data_.title, data_.wight, data_.height);
		glfwTerminate();
		return -2;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(p_window_);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LOG_CRITICAL("Failed to initialize GLAD");
		return -3;
	}

	glfwSetWindowUserPointer(p_window_, &this->data_);

	glfwSetWindowSizeCallback(p_window_, [](GLFWwindow* p_window, int wight, int height) {
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(p_window));
		data.wight = wight;
		data.height = height;

		Event event;
		event.wight = wight;
		event.height = height;
		data.call_back_fn(event);
	});

	return 0;
}

void Window::Shutdown() {
	glfwDestroyWindow(p_window_);
	glfwTerminate();
}

}// end namespace game_engine