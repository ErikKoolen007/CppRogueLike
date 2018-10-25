// CppRogueLike.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Layer.h"
#include <crtdbg.h>
#include "Dungeon.h"

int main()
{
	/*Layer* layer = new Layer{ 5, 5, 1 };
	layer->generate_random_layer();
	for (int i = 0; i < 25; i++)
	{
		std::cout << "Room: " << layer->get_rooms()[i].get_number() << " State: " << layer->get_rooms()[i].get_state() << "\n";
		for(int j = 0; j < 6; j++)
		{
			std::cout << layer->get_rooms()[i].get_hallway(j)->get_level() << "\n";
		}
	}
	layer->draw_layer(1);
	delete layer;*/
	Dungeon* dungeon = new Dungeon{ 5, 5, 5 };
	dungeon->generate_dungeon();
	delete dungeon;

	std::cout << "Memory leaks? (0 for no, 1 for yes. See output for details.)" << _CrtDumpMemoryLeaks() << std::endl;
}
