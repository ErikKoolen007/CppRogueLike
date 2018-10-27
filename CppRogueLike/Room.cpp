#include "Room.h"
#include "Hallway.h"

int Room::get_state() const
{
	return state_;
}

int Room::get_level() const
{
	return level_;
}

int Room::get_number() const
{
	return number_;
}

size_t Room::get_number_of_hallways() const
{
	return number_of_hallways_;
}

Hallway* Room::get_hallway(int index) const
{
	return &hallways_[index];
}

void Room::set_state(int state)
{
	state_ = state;
}
