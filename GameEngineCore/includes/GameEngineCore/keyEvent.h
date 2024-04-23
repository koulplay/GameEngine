#pragma once

#include "GameEngineCore/event.h"
#include <cstdint>

namespace engine {

class EventKey : public EventBase {
public:
	EventKey(const KeyCode key_code)
		: key_(key_code) {}

	KeyCode GetKeyButton() const{
		return key_;
	}
private:
	KeyCode key_;
};

class EventKeyPressed : public EventKey {
public:
	EventKeyPressed(const KeyCode key, const bool repeated)
		: EventKey(key)
		, repeated_(repeated){}

	bool isRepeated() { return repeated_; }

	static EventType GetEventStaticType() {
		return EventType::KEY_PRESSED;
	}

	EventType GetEventType() override {
		return GetEventStaticType();
	}
private:
	bool repeated_;
};

class EventKeyReleased : public EventKey {
public:
	EventKeyReleased(const KeyCode key)
		: EventKey(key) {}

	static EventType GetEventStaticType() {
		return EventType::KEY_RELEASED;
	}

	EventType GetEventType() override {
		return GetEventStaticType();
	}
};

}// end namespace game