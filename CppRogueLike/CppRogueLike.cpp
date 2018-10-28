// CppRogueLike.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <crtdbg.h>
#include "Dungeon.h"
#include "Hero.h"
#include <locale>

void clear_screen()
{
	system("CLS");
}

int ask_number(int min, int max, const char message[])
{
	clear_screen();
	int width{};

	while (true)
	{
		std::cout << "Geef een waarde tussen de " << min << " en " << max << " voor de " << message << " van de dungeon: ";

		if (!(std::cin >> width))
		{
			std::cout << "Geen numerieke waarde!\n";
		}
		else if (width >= min && width <= max)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			return width;
		}

		std::cout << "Geen waarde tussen de " << min << " en " << max << "!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

size_t ask_name(char* char_name, int hero_name_length)
{
	clear_screen();
	size_t name_length{};
	
	while (true)
	{
		std::cout << "Geef je hero een naam van maximaal "<< hero_name_length << " karakters: ";

		for (int i = 0; i < hero_name_length; i++)
		{
			name_length = i;
			if (std::cin.peek() == '\n')
			{
				name_length--;
				break;
			}
			std::cin >> char_name[i];
		}

		const char x = std::cin.get();

		if (x != '\n')
		{
			std::cout << "Er zijn meer dan " << hero_name_length << " karakters ingevuld. Probeer opnieuw\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			name_length++;

			return name_length;
		}
	}
}

bool are_equal(const char* array1, const char* array2)
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

int main()
{
	bool game_loop{ true };
	const int hero_name_length{ 20 };
	const int hero_action_length{ 20 };
	char char_name[hero_name_length]{};
	char action_name[hero_action_length]{};

	const int width = ask_number(2, 10, "breedte");
	const int height = ask_number(2, 10, "lengte");
	const int depth = ask_number(2, 10, "diepte");
	const size_t name_length = ask_name(char_name, hero_name_length);
	clear_screen();

	Dungeon* dungeon = new Dungeon{ width, height, depth };
	Hero* hero = new Hero(char_name, name_length);
	dungeon->generate_dungeon();
	hero->set_layer_number(1);
	hero->set_room_number(dungeon->get_layer(0)->get_start()->get_number());

	while (game_loop)
	{
		std::cout << "Je staat in een ";
		switch (dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_random_room_size())
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
		switch (dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_random_room_cleanliness())
		{
			case 1:
				std::cout << "opgeruimde ";
				break;
			case 2:
				std::cout << "smerige ";
				break;
		}
		std::cout << "kamer. Verder staat er ";
		switch (dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_random_room_furniture())
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

		std::cout << "Wat doe je?\n";
		std::cout << "[ga verder, zoek, rust uit, bekijk spullen, bekijk kaart, bekijk hero info, quit]\n Actie: ";
		std::cin.getline(action_name, hero_action_length);

		if(are_equal(action_name, "ga verder"))
		{
			char direction_name[20]{};
			std::cout << "Welke richting?\n";
			std::cout << "[";
			for (size_t i = 0; i < dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_number_of_hallways(); i++)
			{
				if(dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(i)->get_level() != 0)
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
			std::cout << "Richting: ";
			std::cin.getline(direction_name, 20);

			if(are_equal(direction_name, "noord") && dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(0)->get_level() != 0)
			{
				hero->set_room_number(dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(0)->get_from_room()->get_number());
			}
			else if (are_equal(direction_name, "oost") && dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(1)->get_level() != 0)
			{
				hero->set_room_number(dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(1)->get_to_room()->get_number());
			}
			else if (are_equal(direction_name, "zuid") && dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(2)->get_level() != 0)
			{
				hero->set_room_number(dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(2)->get_to_room()->get_number());
			}
			else if (are_equal(direction_name, "west") && dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(3)->get_level() != 0)
			{
				hero->set_room_number(dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(3)->get_from_room()->get_number());
			}
			else if (are_equal(direction_name, "trap naar boven") && dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(4)->get_level() != 0)
			{
				hero->set_room_number(dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(4)->get_from_room()->get_number());
				hero->set_layer_number(dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(4)->get_from_room()->get_level());
			}
			else if (are_equal(direction_name, "trap naar beneden") && dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(5)->get_level() != 0)
			{
				hero->set_room_number(dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(5)->get_to_room()->get_number());
				hero->set_layer_number(dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_hallway(5)->get_to_room()->get_level());
			}
			else
			{
				std::cout << "Geen geldige richting. Probeer opnieuw(press Enter).\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		else if(are_equal(action_name, "bekijk kaart"))
		{
			dungeon->display_map(hero->get_layer_number(), hero->get_room_number());
		}
		else if (are_equal(action_name, "bekijk hero info"))
		{
			hero->print_hero_info();
		}
		else if (are_equal(action_name, "quit"))
		{
			game_loop = false;
		}
		else if(are_equal(action_name, "debug"))
		{
			dungeon->debug_print();
		}
		else
		{
			std::cout << "Geen geldige actie. Probeer opnieuw(press Enter).\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	delete hero;
	delete dungeon;

	//Memory check
	std::cout << "Memory leaks? (0 for no, 1 for yes. See output for details.)" << _CrtDumpMemoryLeaks() << std::endl;
}
