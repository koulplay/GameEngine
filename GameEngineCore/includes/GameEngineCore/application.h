#pragma once

namespace game_engine {

class Application {
public:
	Application();
	virtual ~Application();

	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

	virtual int Start(unsigned int window_width, unsigned int window_height, const char* title);

	virtual void OnUpdate() {}
};

}// end namespace game_engine