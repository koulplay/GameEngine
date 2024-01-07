#pragma once

#include <string>

struct GLFWwindow;

namespace game_engine {

class Window {
public:
	Window(std::string title, const unsigned int wight, const unsigned int height);
	~Window();

	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;

	void OnUpdate();
	unsigned int GetWight() const;
	unsigned int GetHeight() const;

private:
	int Init();
	void Shutdown();

private:
	GLFWwindow* p_window_;
	std::string title_;
	unsigned int wight_;
	unsigned int height_;
};

}// end namespace game_engine