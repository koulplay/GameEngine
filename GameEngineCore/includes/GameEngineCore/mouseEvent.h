#pragma once

#include "GameEngineCore/event.h"

namespace engine {

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

	static EventType GetEventStaticType() {
		return EventType::MOUSE_BUTTON_PRESSED;
	}

	EventType GetEventType() override {
		return GetEventStaticType();
	}
};

class EventMouseButtonReleased : public EventMouseButton {
public:
	EventMouseButtonReleased(int button)
		: EventMouseButton(button) {}

	static EventType GetEventStaticType() {
		return EventType::MOUSE_BUTTON_RELEASED;
	}

	EventType GetEventType() override {
		return GetEventStaticType();
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

	static EventType GetEventStaticType() {
		return EventType::MOUSE_MOVED;
	}

	EventType GetEventType() override {
		return GetEventStaticType();
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

	static EventType GetEventStaticType() {
		return EventType::MOUSE_SCROLLED;
	}

	EventType GetEventType() override {
		return GetEventStaticType();
	}
private:
	double Xoffset_, Yoffset_;
};

}// end namespace engine