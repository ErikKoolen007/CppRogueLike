#pragma once
#include "Hallway.h"
class Hallway;

class Room
{
	// States: 0 = starting point, 1 = visiting, 2 = visited, 3 = not visited, 4 = end point, 5 = stair down, 6 = stair up.
	int state_;
	// Dungeon has more than one layer, this states what level/layer the room is on.
	int level_;
	// Room number
	int number_;

	int random_room_size_;
	int random_room_furniture_;
	int random_room_cleanliness_;
	int number_of_hallways_;

	/*hallways_[0] = north_hall
	hallways_[1] = east_hall
	hallways_[2] = south_hall
	hallways_[3] = west_hall
	hallways_[4] = stair_up
	hallways_[5] = stair_down*/
	Hallway *hallways_;

public:
	Room() : state_{}, level_{}, number_{}, random_room_size_{}, random_room_furniture_{}, random_room_cleanliness_{},
	         number_of_hallways_{},
	         hallways_{nullptr}
	{
	}

	Room(int state, int level, int number, int room_size, int room_furniture, int room_cleanliness) :
		state_{state}, level_{level}, number_{number}, random_room_size_{ room_size },
		random_room_furniture_{ room_furniture }, random_room_cleanliness_{ room_cleanliness },
		number_of_hallways_{6}, hallways_{new Hallway[ number_of_hallways_]}
	{
	}

	~Room()
	{
		delete[] hallways_;
	}

	//Copy constructor
	Room(const Room &r) : state_{r.state_}, level_{r.level_}, number_{r.number_},
	                      random_room_size_{r.random_room_size_}, random_room_furniture_{r.random_room_furniture_},
						  random_room_cleanliness_{r.random_room_cleanliness_ },
						  number_of_hallways_{ r.number_of_hallways_ },
	                      hallways_{ new Hallway[r.number_of_hallways_] }
	{
		for (int i = 0; i < r.number_of_hallways_; i++)
		{
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
		random_room_size_ = r.random_room_size_;
		random_room_furniture_ = r.random_room_furniture_;
		random_room_cleanliness_ = r.random_room_cleanliness_;
		number_of_hallways_ = r.number_of_hallways_;
		hallways_ = new Hallway[r.number_of_hallways_];

		return *this;
	}

	//Move constructor
	Room(Room &&r) noexcept : state_{r.state_}, level_{r.level_}, number_{r.number_},
	                          random_room_size_{r.random_room_size_}, random_room_furniture_{r.random_room_furniture_},
							  random_room_cleanliness_{ r.random_room_cleanliness_ },
	                          number_of_hallways_(r.number_of_hallways_),
	                          hallways_{r.hallways_}
	{
		r.state_ = r.level_ = r.number_ = 0;
		r.random_room_size_ = r.random_room_furniture_ = r.random_room_cleanliness_ = 0;
		r.number_of_hallways_ = {};
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
		random_room_size_ = r.random_room_size_;
		random_room_furniture_ = r.random_room_furniture_;
		random_room_cleanliness_ = r.random_room_cleanliness_;
		number_of_hallways_ = r.number_of_hallways_;
		hallways_ = r.hallways_;

		r.state_ = r.level_ = r.number_ = 0;
		r.random_room_size_ = r.random_room_furniture_ = r.random_room_cleanliness_ = 0;
		r.number_of_hallways_ = {};
		r.hallways_ = nullptr;

		return *this;
	}

	int get_state() const;
	int get_level() const;
	int get_number() const;
	int get_random_room_size() const;
	int get_random_room_furniture() const;
	int get_random_room_cleanliness() const;
	int get_number_of_hallways() const;
	Hallway* get_hallway(int index) const;
	void set_state(int state);
};
