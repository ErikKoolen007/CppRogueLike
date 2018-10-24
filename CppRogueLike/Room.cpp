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

Hallway* Room::get_hallway(int index) const
{
	return &hallways_[index];
}

void Room::set_state(int state)
{
	state_ = state;
}
