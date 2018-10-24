#pragma once
class Room;

class Hallway
{
	//Hallway level => used for generation
	int level_;

	//From room = north, west or stair_up
	Room* from_room_;
	//To room = south, east, stair_down
	Room* to_room_;

public:
	Hallway() : level_{}, from_room_{ nullptr }, to_room_{ nullptr }
	{
	}

	Hallway(int level, Room& from, Room& to) : level_{ level }, from_room_{ &from }, to_room_{ &to }
	{
	}

	int get_level() const;
	Room* get_from_room() const;
	Room* get_to_room() const;
};

