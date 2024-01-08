#pragma once

namespace game_engine{
	
	struct Event{
		unsigned int wight;
		unsigned int height;
	};

	class MoveEvent : public Event{
		
	};
	
}// end namespace game_engine