#pragma once

#include "GameEngineCore/event.h"
#include <cstdint>

namespace game_engine {

class EventWindowClose : public EventBase {
public:
	EventWindowClose() {}

	EventType GetEventType() override {
		return EventType::WINDOW_CLOSE;
	}
};

class EventWindowResize : public EventBase {
public:
	EventWindowResize(unsigned int width, unsigned int height)
		: width_(width), height_(height) {}

	unsigned int GetWidth() const {
		return width_;
	}
	unsigned int GetHeight() const {
		return height_;
	}

	EventType GetEventType() override {
		return EventType::WINDOW_RESIZE;
	}
private:
	unsigned int width_, height_;
};

}// end namespace game_engine