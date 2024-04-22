#pragma once

#include "GameEngineCore/event.h"
#include <cstdint>

namespace engine {

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

	static EventType GetEventStaticType() {
		return EventType::KEY_PRESSED;
	}

	EventType GetEventType() override {
		return GetEventStaticType();
	}
};

class EventKeyReleased : public EventKey {
public:
	EventKeyReleased(int key)
		: EventKey(key) {}

	static EventType GetEventStaticType() {
		return EventType::KEY_RELEASED;
	}

	EventType GetEventType() override {
		return GetEventStaticType();
	}
};

}// end namespace game