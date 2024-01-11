#pragma once

namespace game_engine {

enum class EventType {
	NONE = 0,
	WINDOW_CLOSE, WINDOW_RESIZE, /*WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,*/
	KEY_PRESSED, KEY_RELEASED, 
	MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED
};

class EventBase {
public:
	virtual ~EventBase() = default;
	virtual EventType GetEventType() = 0;
};

}// end namespace game_engine