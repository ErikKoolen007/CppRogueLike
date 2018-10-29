#include "Utilities.h"
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>

int Utilities::get_random(int min, int max)
{
	const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);

	const std::uniform_int_distribution<int> distribution(min, max);

	return distribution(generator);
}

int Utilities::get_random_item()
{
	const int random_nr = get_random(1, 100);
	if (random_nr >= 1 && random_nr <= 50)
		return 0;
	return get_random(1, 5);
}

bool Utilities::attack_is_hit(int attacker_accuracy, int defender_evasion)
{
	const int random_nr = get_random(1, 100);
	if (random_nr >= 1 && random_nr <= attacker_accuracy)
	{
		const int random_nr_evade = get_random(1, 100);
		if (random_nr >= 1 && random_nr_evade <= defender_evasion)
		{
			std::cout << "Verdediger heeft succesvol ontweken.\n\n";
			return false;
		}
		std::cout << "Aanvaller heeft succesvol aangevallen en ";
		return true;
	}

	std::cout << "Aanval was mis.\n\n";
	return false;
}

bool Utilities::are_equal(const char* array1, const char* array2)
{
	for (int i = 0; array1[i] != '\0' || array2[i] != '\0'; i++)
	{
		if (array1[i] != array2[i])
		{
			return false;
		}
	}

	return true;
}

void Utilities::print_room_description(const Dungeon& dungeon, const Hero& hero)
{
	std::cout << "Je staat in een ";
	switch (dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_random_room_size())
	{
	case 1:
		std::cout << "grote ";
		break;
	case 2:
		std::cout << "gemiddelde ";
		break;
	case 3:
		std::cout << "kleine ";
		break;
	}
	switch (dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_random_room_cleanliness())
	{
	case 1:
		std::cout << "opgeruimde ";
		break;
	case 2:
		std::cout << "smerige ";
		break;
	}
	std::cout << "kamer. Verder staat er ";
	switch (dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_random_room_furniture())
	{
	case 1:
		std::cout << "een tafel met 4 stoelen.\n\n";
		break;
	case 2:
		std::cout << "een bed.\n\n";
		break;
	case 3:
		std::cout << "niks.\n\n";
		break;
	}
}

void Utilities::print_possible_directions(const Dungeon& dungeon, const Hero& hero)
{
	std::cout << "[";
	for (int i = 0; i < dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_number_of_hallways(); i++)
	{
		if (dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(i)->get_level() != 0)
		{
			if (i == 0)
				std::cout << "noord, ";
			if (i == 1)
				std::cout << "oost, ";
			if (i == 2)
				std::cout << "zuid, ";
			if (i == 3)
				std::cout << "west, ";
			if (i == 4)
				std::cout << "trap naar boven, ";
			if (i == 5)
				std::cout << "trap naar beneden";
		}
	}
	std::cout << "]\n";
}

void Utilities::print_item(int item_id)
{
	switch (item_id)
	{
	case 1:
		std::cout << "helm ";
		break;
	case 2:
		std::cout << "pantser ";
		break;
	case 3:
		std::cout << "zwaard ";
		break;
	case 4:
		std::cout << "genezingsdrankje ";
		break;
	case 5:
		std::cout << "granaat ";
		break;
	}
}

void Utilities::move_to_input_direction(Dungeon& dungeon, Hero& hero)
{
	bool invalid_direction{ true };

	while (invalid_direction) 
	{
		char direction_name[20]{};
		std::cout << "Richting: ";
		std::cin.getline(direction_name, 20);
		if (are_equal(direction_name, "noord") && dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(0)->get_level() != 0)
		{
			hero.set_room_number(dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(0)->get_from_room()->get_number());
			invalid_direction = false;
		}
		else if (are_equal(direction_name, "oost") && dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(1)->get_level() != 0)
		{
			hero.set_room_number(dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(1)->get_to_room()->get_number());
			invalid_direction = false;
		}
		else if (are_equal(direction_name, "zuid") && dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(2)->get_level() != 0)
		{
			hero.set_room_number(dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(2)->get_to_room()->get_number());
			invalid_direction = false;
		}
		else if (are_equal(direction_name, "west") && dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(3)->get_level() != 0)
		{
			hero.set_room_number(dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(3)->get_from_room()->get_number());
			invalid_direction = false;
		}
		else if (are_equal(direction_name, "trap naar boven") && dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(4)->get_level() != 0)
		{
			hero.set_room_number(dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(4)->get_from_room()->get_number());
			hero.set_layer_number(dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(4)->get_from_room()->get_level());
			invalid_direction = false;
		}
		else if (are_equal(direction_name, "trap naar beneden") && dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(5)->get_level() != 0)
		{
			hero.set_room_number(dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(5)->get_to_room()->get_number());
			hero.set_layer_number(dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_hallway(5)->get_to_room()->get_level());
			invalid_direction = false;
		}
		else
		{
			std::cout << "Geen geldige richting. Probeer opnieuw(press Enter).\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}

bool Utilities::did_enemy_spawn()
{
	const int number = get_random(1, 2);

	return number == 1;
}

void Utilities::go_search(Dungeon& dungeon, Hero& hero)
{
	if (dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_item_id() == 0)
		std::cout << "Niks gevonden.\n\n";
	else
	{
		std::cout << "Je hebt een ";
		print_item(dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_item_id());
		std::cout << "gevonden.\n\n";

		bool not_done_searching{ true };
		char answer[4];
		while (not_done_searching) {
			std::cout << "Wil je het oppakken?\n\n";
			std::cout << "[ja, nee]\n\nActie: ";
			std::cin.getline(answer, 4);

			if (are_equal(answer, "ja"))
			{
				pickup_item(dungeon, hero);
				not_done_searching = false;
			}
			else if (are_equal(answer, "nee"))
			{
				std::cout << "Je laat het object rustig liggen.\n\n";
				not_done_searching = false;
			}
			else
			{
				std::cout << "Geen geldige actie. Probeer opnieuw(press Enter).\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	}
}

void Utilities::pickup_item(Dungeon& dungeon, Hero& hero)
{
	const int item_id = dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->get_item_id();

	switch (item_id)
	{
	case 1:
		if(!hero.has_head_armor())
		{
			dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->pickup_item();
			hero.equip_head_armor();
			std::cout << "Helm opgepakt.\n";
		}
		else
		{
			std::cout << "Je hero had al een helm.\n";
		}
		break;
	case 2:
		if(!hero.has_chest_armor())
		{
			dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->pickup_item();
			hero.equip_chest_armor();
			std::cout << "Pantser opgepakt.\n";
		}
		else
		{
			std::cout << "Je hero had al een pantser.\n";
		}
		break;
	case 3:
		if(!hero.has_sword())
		{
			dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->pickup_item();
			hero.equip_sword();
			std::cout << "Zwaard opgepakt.\n";
		}
		else
		{
			std::cout << "Je hero had al een zwaard.\n";
		}
		break;
	case 4:
		if(!hero.has_healing_potion())
		{
			dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->pickup_item();
			hero.equip_healing_potion();
			std::cout << "Genezingsdrankje opgepakt.\n";
		}
		else
		{
			std::cout << "Je hero had al een genezingsdrankje.\n";
		}
		break;
	case 5:
		dungeon.get_layer(hero.get_layer_number() - 1)->get_room(hero.get_room_number() - 1)->pickup_item();
		hero.add_grenade();
		std::cout << "Granaat opgepakt.\n";
		break;
	default: 
		std::cout << "Dat item ken ik niet en durf ik daarom niet op te pakken.\n";
		break;
	}
}

void Utilities::save_hero(Hero& hero)
{
	std::ofstream ofs;
	ofs.open("hero.txt", std::ios::trunc);
	if(ofs.is_open())
	{
		ofs << hero;
		ofs.close();
		std::cout << "Hero saved!\n\n";
	}
	else
	{
		std::cout << "\n\n\n\nUnable to open file\n\n\n\n";
	}
	
}
