#include "Hallway.h"

int Hallway::get_level() const
{
	return level_;
}

Room* Hallway::get_from_room() const
{
	return from_room_;
}

Room* Hallway::get_to_room() const
{
	return to_room_;
}
