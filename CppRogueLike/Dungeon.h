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

	Layer* get_layer(int index) const;
	void generate_dungeon();
	void display_map(int player_layer_nr, int player_room_nr) const;
	void debug_print() const;
};

