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

	while (!close_window_){
		p_window_->OnUpdate();
		this->OnUpdate();
	}
	p_window_ = nullptr;
	return 0;
}

void Application::OnEvent(EventBase& event) {
	EventDispatcher dispatcher(event);

	dispatcher.Dispatch<EventWindowClose>([this](EventWindowClose& event) {
		LOG_INFO("[CORE] [EVENT] Window Close");
		close_window_ = true;
	});

	dispatcher.Dispatch<EventWindowResize>([this](EventWindowResize& event) {
		//LOG_INFO("[CORE] [EVENT] Changed size to {0}x{1}", event.GetWidth(), event.GetHeight());
	});

	dispatcher.Dispatch<EventMouseMoved>([this](EventMouseMoved& event) {
		//LOG_INFO("[CORE] [EVENT] Mouse moved to {0}x{1}", event.GetMouseX(), event.GetMouseY());
	});
}

bool Application::OnWindowClose(EventWindowClose& event) {
	close_window_ = true;
	return true;
}

}// end namespace game_engine