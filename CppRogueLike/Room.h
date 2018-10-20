#pragma once
#include "Hallway.h"

class Room
{
	// States: 0 = starting point, 1 = visiting, 2 = visited, 3 = not visited, 4 = end point.
	int state_;
	// Dungeon has more than one layer, this states what level/layer the room is on.
	int level_;
	// Room number
	int number_;

	Hallway *west_hall_;
	Hallway *east_hall_;
	Hallway *north_hall_;
	Hallway *south_hall_;
	Hallway *stair_up_;
	Hallway *stair_down_;

public:
	Room(int state, int level, int number) : state_(state), level_(level), number_(number)
	{
		west_hall_ = nullptr;
		east_hall_ = nullptr;
		north_hall_ = nullptr;
		south_hall_ = nullptr;
		stair_up_ = nullptr;
		stair_down_ = nullptr;
	}

	int get_state() const;
	int get_level() const;
	int get_number() const;
};

