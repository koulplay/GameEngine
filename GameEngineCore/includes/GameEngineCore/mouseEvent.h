#pragma once

#include "GameEngineCore/event.h"

namespace game_engine {

class EventMouseButton : public EventBase {
public:
	EventMouseButton(int mouse_button)
		: mouse_button_(mouse_button) {}

	int GetMouseButton() const {
		return mouse_button_;
	}
private:
	int mouse_button_;
};

class EventMouseButtonPressed : public EventMouseButton {
public:
	EventMouseButtonPressed(int button)
	: EventMouseButton(button){}

	EventType GetEventType() override {
		return event_type_;
	}
private:
	const static EventType event_type_ = EventType::MOUSE_BUTTON_PRESSED;
};

class EventMouseButtonReleased : public EventMouseButton {
public:
	EventMouseButtonReleased(int button)
		: EventMouseButton(button) {}

	EventType GetEventType() override {
		return event_type_;
	}
private:
	const static EventType event_type_ = EventType::MOUSE_BUTTON_RELEASED;
};

class EventMouseMoved : public EventBase {
public:
	EventMouseMoved(double mouseX, double mouseY)
		: mouseX_(mouseX), mouseY_(mouseY){}

	EventType GetEventType() override {
		return event_type_;
	}
private:
	double mouseX_, mouseY_;

	const static EventType event_type_ = EventType::MOUSE_MOVED;
};

class EventMouseScrolled : public EventBase {
public:
	EventMouseScrolled(double Xoffset, double Yoffset)
		: Xoffset_(Xoffset), Yoffset_(Yoffset) {}

	EventType GetEventType() override {
		return event_type_;
	}
private:
	double Xoffset_, Yoffset_;

	const static EventType event_type_ = EventType::MOUSE_SCROLLED;
};

}// end namespace game_engine