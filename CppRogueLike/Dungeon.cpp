#include "Dungeon.h"
#include "Utilities.h"

void Dungeon::generate_dungeon()
{
	for (size_t i = 0; i < number_of_layers_; i++)
	{
		const int layer_number = i + 1;
		layers_[i] = Layer(width_, height_, layer_number);
		layers_[i].generate_random_layer();

		//Create stairs
		if (i != 0) {
			layers_[i].set_start(*layers_[i - 1].get_end());
			layers_[i].get_start()->set_state(6);
		}

		layers_[i].set_end(layers_[i].get_rooms()[Utilities::get_random(0, layers_[i].get_number_of_rooms() - 1)]);

		//If start == end -> find another end
		while (layers_[i].get_start()->get_number() == layers_[i].get_end()->get_number())
		{
			layers_[i].set_end(layers_[i].get_rooms()[Utilities::get_random(0, layers_[i].get_number_of_rooms() - 1)]);
		}
		if(i == number_of_layers_ - 1)
			layers_[i].get_end()->set_state(4);
		else
			layers_[i].get_end()->set_state(5);

		layers_[i].draw_layer(1);
	}
}
