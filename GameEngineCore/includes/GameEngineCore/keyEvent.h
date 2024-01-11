#pragma once

#include "GameEngineCore/event.h"
#include <cstdint>

namespace game_engine {

class EventKey : public EventBase {
public:
	EventKey(int key)
		: key_(key) {}

	int GetKeyButton() const{
		return key_;
	}
private:
	int key_;
};

class EventKeyPressed : public EventKey {
public:
	EventKeyPressed(int key)
		: EventKey(key) {}

	EventType GetEventType() override {
		return event_type_;
	}
private:
	const static EventType event_type_ = EventType::KEY_PRESSED;
};

class EventKeyReleased : public EventKey {
public:
	EventKeyReleased(int key)
		: EventKey(key) {}

	EventType GetEventType() override {
		return event_type_;
	}
private:
	const static EventType event_type_ = EventType::KEY_RELEASED;
};

}// end namespace game