#pragma once

#include <GameEngineCore/windowEvent.h>
#include <GameEngineCore/keyEvent.h>
#include <GameEngineCore/mouseEvent.h>

#include <memory>

namespace game_engine {

class Application {
public:
	Application();
	virtual ~Application();

	Application(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(const Application&) = delete;
	Application& operator=(Application&&) = delete;

	virtual int Start(unsigned int window_wight, unsigned int window_height, const char* title);

	virtual void OnUpdate() {}
	void OnEvent(EventBase& event);

private:
	std::unique_ptr<class Window> p_window_;
};

}// end namespace game_engine