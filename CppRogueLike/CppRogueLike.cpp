// CppRogueLike.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <crtdbg.h>
#include "Dungeon.h"
#include "Hero.h"

int main()
{
	int width, height, depth{};

	std::cout << "Geef een waarde tussen de 2 en 10 voor de breedte van de dungeon: ";
	while(!(std::cin >> width))
	{
		std::cout << "Geen numerieke waarde!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	char char_name[20]{};
	size_t name_length{};
	bool invalid_name{ true };

	std::cout << "Geef je hero een naam van maximaal 20 karakters: ";
	while(invalid_name)
	{
		for(int i = 0; i < 20; i++)
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
			std::cout << "Er zijn meer dan 20 karakters ingevuld. Probeer opnieuw\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			invalid_name = false;
			name_length++;
		}
	}



	Dungeon* dungeon = new Dungeon{ 5, 5, 3 };
	Hero* hero = new Hero(char_name, name_length);
	hero->print_hero_info();
	dungeon->generate_dungeon();
	dungeon->display_map(0, 5);
	//dungeon->debug_print();
	delete hero;
	delete dungeon;

	std::cout << "Memory leaks? (0 for no, 1 for yes. See output for details.)" << _CrtDumpMemoryLeaks() << std::endl;
}
