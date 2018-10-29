#include "Spawner.h"
#include <fstream>
#include <iostream>
#include "Utilities.h"

Monster* Spawner::spawn_random_monster(int current_layer_nr, int layer_count, bool is_boss)
{
	//Get file
	std::ifstream input("monsters.txt");
	if (input.is_open())
	{
		try
		{
			monster_ = new Monster();
		}
		catch (std::bad_alloc & ba)
		{
			std::cerr << "bad_alloc caught when creating monster: " << ba.what() << "\n";
			return nullptr;
		}

		//Get random spawn number
		int spawn_enemy_line;
		if(current_layer_nr == 1)
		{
			spawn_enemy_line = Utilities::get_random(1, 4);
		}
		else if(current_layer_nr == layer_count)
		{
			spawn_enemy_line = Utilities::get_random(10, 12);
		}
		else
		{
			spawn_enemy_line = Utilities::get_random(5, 9);
		}

		if(is_boss)
		{
			spawn_enemy_line = Utilities::get_random(13, 14);
		}

		//Ignore monsters till chosen one
		for (int i = 1; i < spawn_enemy_line; i++) {
			input.ignore(std::numeric_limits<std::streamsize>::max(), input.widen('\n'));
		}

		//Read chosen monster from file
		if (input.get() == '[') {
			char buffer[20];
			int name_size;
			int int_buffer;

			input >> name_size;
			for (int i = 0; i < name_size; i++)
			{
				if(input.peek() == input.narrow(' '))
				{
					buffer[i] = ' ';
					input.ignore(1);
				}
				else
				{
					input >> buffer[i];
				}
			}
			monster_->set_name_size(name_size);
			monster_->create_name(buffer, name_size);
			input.get();
			input >> int_buffer;
			monster_->set_level(int_buffer);
			input.get();
			input >> int_buffer;
			monster_->set_accuracy(int_buffer);
			input.get();
			input >> int_buffer;
			monster_->set_attack_amount(int_buffer);
			input.get();
			input >> int_buffer;
			monster_->set_min_damage(int_buffer);
			input.get();
			input >> int_buffer;
			monster_->set_max_damage(int_buffer);
			input.get();
			input >> int_buffer;
			monster_->set_defence(int_buffer);
			input.get();
			input >> int_buffer;
			monster_->set_health(int_buffer);
		}
		return monster_;
	}

	std::cout << "Unable to open file\n";
	return nullptr;
}

void Spawner::destroy_monster()
{
	delete monster_;
	monster_ = nullptr;
}
