#include <GameEngineCore/window.h>
#include <GameEngineCore/log.h>
#include <GameEngineCore/windowEvent.h>
#include <GameEngineCore/mouseEvent.h>
#include <GameEngineCore/keyEvent.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <utility>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

namespace game_engine {

static bool is_GLFW_initialized = false;

Window::Window(std::string title, const unsigned int wight, const unsigned int height)
	: data_({ std::move(title), wight, height }) {
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
	if (!is_GLFW_initialized){
		if(!glfwInit()){
			LOG_CRITICAL("[CORE] Can\'t initialize GLFW!");
			return -1;
		}
			
		is_GLFW_initialized = true;
	}

	/* Create a windowed mode window and its OpenGL context */
	p_window_ = glfwCreateWindow(data_.wight, data_.height, data_.title.c_str(), nullptr, nullptr);
	if(!p_window_) {
		LOG_CRITICAL("[CORE] Can\'t create window '{0}' with size {1}x{2}", data_.title, data_.wight, data_.height);
		glfwTerminate();
		return -2;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(p_window_);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
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

	ImGui::ShowDemoWindow();

	ImGui::Begin("Background Color Window");
	ImGui::ColorEdit4("Background Color", background_color_);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	glfwSwapBuffers(p_window_);
	glfwPollEvents();
}

void Window::Shutdown() {
	glfwDestroyWindow(p_window_);
	glfwTerminate();
}

}// end namespace game_engine