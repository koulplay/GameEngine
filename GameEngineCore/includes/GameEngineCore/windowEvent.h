#pragma once

#include "GameEngineCore/event.h"
#include <cstdint>

namespace game_engine {

class EventWindowClose : public EventBase {
public:
	EventWindowClose() {}

	EventType GetEventType() override {
		return event_type_;
	}
private:
	const static EventType event_type_ = EventType::WINDOW_CLOSE;
};

class EventWindowResize : public EventBase {
public:
	EventWindowResize(int width, int height)
		: width_(width), height_(height) {}

	EventType GetEventType() override {
		return event_type_;
	}
private:
	int width_, height_;

	const static EventType event_type_ = EventType::WINDOW_RESIZE;
};

}// end namespace game_engine