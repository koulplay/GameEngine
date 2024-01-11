#include <GameEngineCore/application.h>
#include <GameEngineCore/log.h>
#include <GameEngineCore/window.h>

#include <iostream>


namespace game_engine {

Application::Application() {
	LOG_INFO("[CORE] Starting Application");

}
Application::~Application() {
	LOG_INFO("[CORE] Closing Application");
}

int Application::Start(unsigned int window_width, unsigned int window_height, const char* title) {
	p_window_ = std::make_unique<Window>(title, window_width, window_height);
	p_window_->SetEventCallback([this](EventBase& event) {this->OnEvent(event); });

	while (true){
		p_window_->OnUpdate();
		this->OnUpdate();
	}
	return 0;
}

void Application::OnEvent(EventBase& event) {
	auto resize_event = static_cast<EventWindowResize*>(&event);
	LOG_INFO("[CORE] [EVENT] Changed size to {0}x{1}", resize_event->GetWidth(), resize_event->GetHeight());
}

}// end namespace game_engine