// CppRogueLike.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <crtdbg.h>
#include "Dungeon.h"

int main()
{
	Dungeon* dungeon = new Dungeon{ 5, 5, 3 };
	dungeon->generate_dungeon();
	dungeon->display_map(0, 5);
	//dungeon->debug_print();
	delete dungeon;

	std::cout << "Memory leaks? (0 for no, 1 for yes. See output for details.)" << _CrtDumpMemoryLeaks() << std::endl;
}
