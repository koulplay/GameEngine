#pragma once

#include <GameEngineCore/event.h>

#include <string>
#include <functional>

struct GLFWwindow;

namespace game_engine {

class Window {
public:
	using EventCallbackFn = std::function<void(Event&)>;

	Window(std::string title, const unsigned int wight, const unsigned int height);
	~Window();

	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;

	void OnUpdate();
	unsigned int GetWight() const;
	unsigned int GetHeight() const;

	void SetEventCallback(const EventCallbackFn& callback);

private:
	int Init();
	void Shutdown();

private:
	struct WindowData{
		std::string title;
		unsigned int wight;
		unsigned int height;
		EventCallbackFn call_back_fn;
	};

	GLFWwindow* p_window_;
	WindowData data_;
};

}// end namespace game_engine