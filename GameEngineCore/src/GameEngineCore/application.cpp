#include <GameEngineCore/application.h>
#include <GameEngineCore/log.h>
#include <GameEngineCore/window.h>

#include <iostream>

namespace game_engine {

Application::Application() {
	LOG_INFO("Starting Application");

}
Application::~Application() {
	LOG_INFO("Closing Application");
}

int Application::Start(unsigned int window_width, unsigned int window_height, const char* title) {
	p_window_ = std::make_unique<Window>(title, window_width, window_height);
	p_window_->SetEventCallback([](Event& event){
		LOG_INFO("[EVENT] Changed size to {0}x{1}", event.wight, event.height);
	});

	while (true){
		p_window_->OnUpdate();
		this->OnUpdate();
	}

	return 0;
}

}// end namespace game_engine