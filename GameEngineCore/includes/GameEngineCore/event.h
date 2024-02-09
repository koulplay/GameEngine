#pragma once

#include <functional>

namespace game_engine {

enum class EventType {
	NONE = 0,
	WINDOW_CLOSE, WINDOW_RESIZE, /*WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,*/
	KEY_PRESSED, KEY_RELEASED,
	MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED
};

class EventBase {
public:
	friend class EventDispatcher;

	virtual ~EventBase() = default;
	virtual EventType GetEventType() = 0;
};

class EventDispatcher {
public:
	EventDispatcher(EventBase& event)
		: event_(event) {}

	template<typename EventType>
	void Dispatch(std::function<void(EventType&)> func) {
		if(event_.GetEventType() == EventType::GetEventStaticType()) {
			func(static_cast<EventType&>(event_));
		}
	}
private:
	EventBase& event_;
};

}// end namespace game_engine