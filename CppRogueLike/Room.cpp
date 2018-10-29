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

int Room::get_random_room_size() const
{
	return random_room_size_;
}

int Room::get_random_room_furniture() const
{
	return random_room_furniture_;
}

int Room::get_random_room_cleanliness() const
{
	return random_room_cleanliness_;
}

int Room::get_number_of_hallways() const
{
	return number_of_hallways_;
}

int Room::get_item_id() const
{
	return item_id_;
}

Hallway* Room::get_hallway(int index) const
{
	return &hallways_[index];
}

void Room::set_state(int state)
{
	state_ = state;
}

void Room::pickup_item()
{
	item_id_ = 0;
}
