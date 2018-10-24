#pragma once
#include "Room.h"

class Layer
{
	int x_;
	int y_;
	int layer_nr_;
	Room* start_;
	Room* end_;
	Room* rooms_;

public:
	Layer(int size_x, int size_y, int layer_nr) : x_{ size_x }, y_{ size_y }, layer_nr_{ layer_nr }, start_{ nullptr },
												  end_{ nullptr },
												  rooms_{ new Room[size_x * size_y] }
	{
	}

	~Layer()
	{
		delete[] rooms_;
	}

	const Room* get_start() const;
	const Room* get_end() const;
	const Room* get_rooms() const;
	void set_start(Room& start);
	void set_end(Room& end);

	void generate_random_layer();
};

