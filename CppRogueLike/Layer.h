#pragma once
#include "Room.h"

class Layer
{
	int x_;
	int y_;
	int layer_nr_;
	int number_of_rooms_;
	Room* start_;
	Room* end_;
	Room* rooms_;

public:
	Layer() : x_{}, y_{}, layer_nr_{}, number_of_rooms_{}, start_{ nullptr }, end_{ nullptr }, rooms_{ nullptr }
	{
	}

	Layer(int size_x, int size_y, int layer_nr) : x_{size_x}, y_{size_y}, layer_nr_{layer_nr}, number_of_rooms_(size_x * size_y),
	                                              start_{nullptr},
	                                              end_{nullptr},
	                                              rooms_{new Room[number_of_rooms_]}
	{
	}

	~Layer()
	{
		delete[] rooms_;
	}

	//Copy constructor
	Layer(const Layer &l) : x_{ l.x_ }, y_{ l.y_ }, layer_nr_{ l.layer_nr_ }, number_of_rooms_{ l.number_of_rooms_ },
							start_{ l.start_ }, end_{ l.end_ }, rooms_{ new Room[l.number_of_rooms_] }
	{
		for (int i = 0; i < l.number_of_rooms_; i++) {
			rooms_[i] = l.rooms_[i];
		}
	}

	//Copy assignment operator
	Layer &operator=(const Layer &l)
	{
		if (&l == this)
			return *this;

		delete[] rooms_;

		x_ = l.x_;
		y_ = l.y_;
		layer_nr_ = l.layer_nr_;
		number_of_rooms_ = l.number_of_rooms_;
		start_ = l.start_;
		end_ = l.end_;
		rooms_ = new Room[l.number_of_rooms_];

		return *this;
	}

	//Move constructor
	Layer(Layer &&l) noexcept : x_{ l.x_ }, y_{ l.y_ }, layer_nr_{ l.layer_nr_ }, number_of_rooms_{ l.number_of_rooms_ },
								start_{ l.start_ }, end_{ l.end_ }, rooms_{ l.rooms_ }
	{
		l.x_ = l.y_ = l.layer_nr_ = 0;
		l.number_of_rooms_ = {};
		l.start_ = l.end_ = l.rooms_ = nullptr;
	}

	//Move assignment operator 
	Layer &operator=(Layer &&l) noexcept
	{
		if (&l == this)
			return *this;

		delete[] rooms_;

		x_ = l.x_;
		y_ = l.y_;
		layer_nr_ = l.layer_nr_;
		number_of_rooms_ = l.number_of_rooms_;
		start_ = l.start_;
		end_ = l.end_;
		rooms_ = l.rooms_;

		l.x_ = l.y_ = l.layer_nr_ = 0;
		l.number_of_rooms_ = {};
		l.start_ = l.end_ = l.rooms_ = nullptr;

		return *this;
	}

	Room* get_start() const;
	Room* get_end() const;
	int get_layer_nr() const;
	Room* get_room(int index) const;
	int get_number_of_rooms() const;
	void set_start(Room& start);
	void set_end(Room& end);

	void generate_random_layer();
	static const char* print_character(int state);
	void draw_layer(int player_room_number) const;
};

