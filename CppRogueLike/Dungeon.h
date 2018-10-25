#pragma once
#include "Layer.h"

class Dungeon
{
	int width_;
	int height_;
	size_t number_of_layers_;
	Layer* layers_;
public:
	Dungeon(int width, int height, size_t layer_count) : width_{ width }, height_{ height }, number_of_layers_{ layer_count }, layers_{ new Layer[number_of_layers_] }
	{
	}

	~Dungeon()
	{
		delete[] layers_;
	}

	void generate_dungeon();
};

