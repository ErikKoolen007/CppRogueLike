#include "Dungeon.h"
#include "Utilities.h"
#include <iostream>

Layer* Dungeon::get_layer(int index) const
{
	return &layers_[index];
}

void Dungeon::generate_dungeon() const
{
	for (int i = 0; i < number_of_layers_; i++)
	{
		const int layer_number = i + 1;
		layers_[i] = Layer(width_, height_, layer_number);
		layers_[i].generate_random_layer();

		//Create stairs
		if (i != 0) {
			const int prev_layer_room_nr = layers_[i - 1].get_end()->get_number();
			layers_[i].set_start(*layers_[i].get_room(prev_layer_room_nr - 1));
			layers_[i].get_start()->set_state(6);

			//Create hallway between stair up and down
			const int start_room_nr = layers_[i].get_start()->get_number();
			*layers_[i - 1].get_room(start_room_nr - 1)->get_hallway(5) = Hallway{ 1, *layers_[i - 1].get_room(start_room_nr - 1), *layers_[i].get_room(start_room_nr - 1) };
			*layers_[i].get_room(start_room_nr - 1)->get_hallway(4) = *layers_[i - 1].get_room(start_room_nr - 1)->get_hallway(5);
		}

		layers_[i].set_end(*layers_[i].get_room(Utilities::get_random(0, layers_[i].get_number_of_rooms() - 1)));

		//If start == end -> find another end
		while (layers_[i].get_start()->get_number() == layers_[i].get_end()->get_number())
		{
			layers_[i].set_end(*layers_[i].get_room(Utilities::get_random(0, layers_[i].get_number_of_rooms() - 1)));
		}
		if(i == number_of_layers_ - 1)
			layers_[i].get_end()->set_state(4);
		else
			layers_[i].get_end()->set_state(5);
	}
}

void Dungeon::display_map(int player_layer_nr, int player_room_nr) const
{
	this->get_layer(player_layer_nr - 1)->draw_layer(player_room_nr);
}

void Dungeon::debug_print() const
{
	for (int x = 0; x < number_of_layers_; x++)
	{
		std::cout << "Layer: " << this->get_layer(x)->get_layer_nr() << "\n";

		for (int i = 0; i < this->get_layer(x)->get_number_of_rooms(); i++)
		{
			std::cout << "Room: " << this->get_layer(x)->get_room(i)->get_number() << " State: " << this->get_layer(x)->get_room(i)->get_state() << "\n";

			for (int j = 0; j < this->get_layer(x)->get_room(i)->get_number_of_hallways(); j++)
			{
				std::cout << this->get_layer(x)->get_room(i)->get_hallway(j)->get_level() << "\n";
			}
		}
	}
}
