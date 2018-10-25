#include "Layer.h"
#include "Utilities.h"
#include "Hallway.h"
#include <iostream>

Room* Layer::get_start() const
{
	return start_;
}

Room* Layer::get_end() const
{
	return end_;
}

Room* Layer::get_rooms() const
{
	return rooms_;
}

size_t Layer::get_number_of_rooms() const
{
	return number_of_rooms_;
}

void Layer::set_start(Room& start)
{
	start_ = &start;
}

void Layer::set_end(Room& end)
{
	end_ = &end;
}

void Layer::generate_random_layer()
{
	int number { 1 };

	for (int row{}; row < y_; row++)
	{
		for (int column{}; column < x_; column++)
		{
			//Create rooms with a state, layer number and room number
			rooms_[row * x_ + column] = Room{ 3, layer_nr_, number };
			number++;

			//Create hallways
			if (column >= 1)
			{
				const int previous_column{ column - 1 };

				//First create right hallway of previous room in same row
				*rooms_[row * x_ + previous_column].get_hallway(1) = Hallway(Utilities::get_random(1, 9), rooms_[row * x_ + previous_column], rooms_[row * x_ + column]);

				//Then set leftEdge of current vertex to previous vertex's rightEdge
				*rooms_[row * x_ + column].get_hallway(3) = *rooms_[row * x_ + previous_column].get_hallway(1);
			}
			if (row >= 1)
			{
				const int previous_row{ row - 1 };

				//First create down edge of vertex in same column but previous row
				*rooms_[previous_row * x_ + column].get_hallway(2) = Hallway(Utilities::get_random(1, 9), rooms_[previous_row * x_ + column], rooms_[row * x_ + column]);

				//Then set upEdge of current vertex to previous vertex's downEdge
				*rooms_[row * x_ + column].get_hallway(0) = *rooms_[previous_row * x_ + column].get_hallway(2);
			}
		}
	}

	if(layer_nr_ == 1)
	{
		//Create start
		start_ = &rooms_[Utilities::get_random(0, x_ * y_ - 1)];
		start_->set_state(0);
	}
}

const char* Layer::print_character(int state)
{
	switch (state)
	{
		case 0:
			return "\033[32mS\033[0m";//Green S
		case 1:
			return "\033[34mX\033[0m";//Blue X
		case 2:
			return "*";
		case 4:
			return "E";
		case 5:
			return "L";
		case 6:
			return "H";
		default: 
			return " ";
	}
}

void Layer::draw_layer(int player_room_number) const
{
	//Here, \033 is the ESC character, ASCII 27. 
	//It is followed by [, then zero or more numbers separated by ;
	//and finally the letter m. 
	//The numbers describe the colour and format to switch to from that point onwards.
	//https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal

	char x_room_top[19] = "\033[31m---   ---\033[0m";//Red
	char x_room_wall[19] = "\033[31m|       |\033[0m";//Red
	char x_hallway[5] = "____";
	char y_hallway[14] = "   | |       ";
	char y_hallway_empty[14] = "             ";
	char y_hallway_end[7] = "   | |";
	char y_hallway_end_empty[7] = "      ";
	char x_empty[5] = "    ";

	/*for (int j = 0; j < 5; j++) {
		Room* test = &rooms_[Utilities::get_random(0, x_ * y_ - 1)];
		for (size_t i = 0; i < test->get_number_of_hallways(); i++)
		{
			test->get_hallway_array()[i].set_level(0);
		}
	}*/
	for (int row{}; row < y_; row++)
	{
		for (int column{}; column < x_; column++)
		{
			if(column < x_ - 1)
				std::cout << x_room_top << x_empty;
			else
				std::cout << x_room_top << "\n";
		}
		for (int column{}; column < x_; column++)
		{
			if (column < x_ - 1) 
			{
				if(rooms_[row * x_ + column].get_hallway(1)->get_level() != 0)
					std::cout << x_room_wall << x_hallway;
				else
					std::cout << x_room_wall << x_empty;
			}
			else
				std::cout << x_room_wall << "\n";
		}
		for (int column{}; column < x_; column++)
		{
			if(player_room_number == rooms_[row * x_ + column].get_number())
				std::cout << x_empty << print_character(1);
			else
				std::cout << x_empty << print_character(rooms_[row * x_ + column].get_state());

			if(rooms_[row * x_ + column].get_hallway(1)->get_level() != 0)
				std::cout << x_empty << x_hallway;
			else
				std::cout << x_empty << x_empty;
			if (column == x_ - 1)
				std::cout << "\n";
		}
		for (int column{}; column < x_; column++)
		{
			if (column < x_ - 1)
				std::cout << x_room_wall << x_empty;
			else
				std::cout << x_room_wall << "\n";
		}
		for (int column{}; column < x_; column++)
		{
			if (column < x_ - 1)
				std::cout << x_room_top << x_empty;
			else
				std::cout << x_room_top << "\n";
		}
		for (int i = 0; i < 2; i++) {
			for (int column{}; column < x_; column++)
			{
				if (rooms_[row * x_ + column].get_hallway(2)->get_level() != 0) {
					if (column < x_ - 1)
						std::cout << y_hallway;
					else
						std::cout << y_hallway_end << "\n";
				}
				else
				{
					if (column < x_ - 1)
						std::cout << y_hallway_empty;
					else
						std::cout << y_hallway_end_empty << "\n";
				}
			}
		}
	}
}
