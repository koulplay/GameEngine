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
		return EventType::MOUSE_BUTTON_PRESSED;
	}
};

class EventMouseButtonReleased : public EventMouseButton {
public:
	EventMouseButtonReleased(int button)
		: EventMouseButton(button) {}

	EventType GetEventType() override {
		return EventType::MOUSE_BUTTON_RELEASED;
	}
};

class EventMouseMoved : public EventBase {
public:
	EventMouseMoved(double mouseX, double mouseY)
		: mouseX_(mouseX), mouseY_(mouseY){}

	double GetMouseX() const {
		return mouseX_;
	}
	double GetMouseY() const {
		return mouseY_;
	}

	EventType GetEventType() override {
		return EventType::MOUSE_MOVED;
	}
private:
	double mouseX_, mouseY_;
};

class EventMouseScrolled : public EventBase {
public:
	EventMouseScrolled(double Xoffset, double Yoffset)
		: Xoffset_(Xoffset), Yoffset_(Yoffset) {}

	double GetXOffset() const {
		return Xoffset_;
	}
	double GetYOffset() const {
		return Yoffset_;
	}

	EventType GetEventType() override {
		return EventType::MOUSE_SCROLLED;
	}
private:
	double Xoffset_, Yoffset_;
};

}// end namespace game_engine