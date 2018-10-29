#pragma once
#include "Dungeon.h"
#include "Hero.h"

class Utilities
{
	Utilities() = default;
public:
	static int get_random(int min, int max);
	static int get_random_item();
	static bool attack_is_hit(int attacker_accuracy, int defender_evasion);
	static bool are_equal(const char* array1, const char* array2);
	static void print_room_description(const Dungeon& dungeon, const Hero& hero);
	static void print_possible_directions(const Dungeon& dungeon, const Hero& hero);
	static void print_item(int item_id);
	static void move_to_input_direction(Dungeon& dungeon, Hero& hero);
	static bool did_enemy_spawn();
	static void go_search(Dungeon& dungeon, Hero& hero);
	static void pickup_item(Dungeon& dungeon, Hero& hero);
	static void save_hero(Hero& hero);
};

