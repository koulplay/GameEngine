#include <GameEngineCore/window.h>
#include <GameEngineCore/log.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utility>

namespace game_engine {

static bool is_GLFW_initialized = false;

Window::Window(std::string title, const unsigned int wight, const unsigned int height)
	: title_(std::move(title))
	, wight_(wight)
	, height_(height) {
	int result_code = Init();
}

Window::~Window() {

}

unsigned int Window::GetWight() const { return wight_; }

unsigned int Window::GetHeight() const { return height_; }

void Window::OnUpdate() {
	glClearColor(1, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(p_window_);
	glfwPollEvents();
}

int Window::Init() {
	LOG_INFO("Creating window '{0}' with size {1}x{2}", title_, wight_, height_);

	/* Initialize the library */
	if (!is_GLFW_initialized){
		if(!glfwInit()){
			LOG_CRITICAL("Can\'t initialize GLFW!");
			return -1;
		}
			
		is_GLFW_initialized = true;
	}

	/* Create a windowed mode window and its OpenGL context */
	p_window_ = glfwCreateWindow(wight_, height_, title_.c_str(), nullptr, nullptr);
	if(!p_window_) {
		LOG_CRITICAL("Can\'t create window '{0}' with size {1}x{2}", title_, wight_, height_);
		glfwTerminate();
		return -2;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(p_window_);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		LOG_CRITICAL("Failed to initialize GLAD");
		return -3;
	}

	return 0;
}

void Window::Shutdown() {
	glfwDestroyWindow(p_window_);
	glfwTerminate();
}

}// end namespace game_engine