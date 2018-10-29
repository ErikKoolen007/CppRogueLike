#pragma once
#include "Monster.h"

class Spawner
{
	Monster* monster_;
public:
	Spawner() : monster_(nullptr)
	{
	}
	~Spawner()
	{
		delete monster_;
	}
	Monster* spawn_random_monster(int current_layer_nr, int layer_count, bool is_boss);
	void destroy_monster();
};

