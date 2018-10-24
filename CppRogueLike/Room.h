#pragma once
#include "Hallway.h"
class Hallway;

class Room
{
	// States: 0 = starting point, 1 = visiting, 2 = visited, 3 = not visited, 4 = end point.
	int state_;
	// Dungeon has more than one layer, this states what level/layer the room is on.
	int level_;
	// Room number
	int number_;

	/*hallways_[0] = north_hall
	hallways_[1] = east_hall
	hallways_[2] = south_hall
	hallways_[3] = west_hall
	hallways_[4] = stair_up
	hallways_[5] = stair_down*/
	Hallway *hallways_;

public:
	Room() : state_{}, level_{}, number_{}, hallways_{nullptr}
	{
	}

	Room(int state, int level, int number) : state_{ state }, level_{ level }, number_{ number }, hallways_{new Hallway[6]}
	{
	}

	~Room()
	{
		delete[] hallways_;
	}

	//Copy constructor
	Room(const Room &r) : state_{ r.state_ }, level_{ r.level_ }, number_{ r.number_ }, hallways_{ new Hallway[6] }
	{
		for (int i = 0; i < 6; i++) {
			hallways_[i] = r.hallways_[i];
		}
	}

	//Copy assignment operator
	Room &operator=(const Room &r)
	{
		if(&r == this)
			return *this;

		delete[] hallways_;

		state_ = r.state_;
		level_ = r.level_;
		number_ = r.number_;
		hallways_ = new Hallway[6];

		return *this;
	}

	//Move constructor
	Room(Room &&r) noexcept :state_{ r.state_ }, level_{ r.level_ }, number_{ r.number_ }, hallways_{ r.hallways_ }
	{
		r.state_ = r.level_ = r.number_ = 0;
		r.hallways_ = nullptr;
	}

	//Move assignment operator
	Room &operator=(Room &&r) noexcept
	{
		if (&r == this)
			return *this;

		delete[] hallways_;

		state_ = r.state_;
		level_ = r.level_;
		number_ = r.number_;
		hallways_ = r.hallways_;

		r.state_ = r.level_ = r.number_ = 0;
		r.hallways_ = nullptr;

		return *this;
	}

	int get_state() const;
	int get_level() const;
	int get_number() const;
	Hallway* get_hallway(int index) const;
	void set_state(int state);
};
