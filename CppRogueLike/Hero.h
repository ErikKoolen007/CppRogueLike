#pragma once

class Hero
{
	char* name_;
	size_t name_size_;
	int level_;
	int health_;
	int xp_;
	int accuracy_;
	int evasion_;
	int layer_number_;
	int room_number_;

public:
	Hero(const char name[], size_t name_length) : name_{ new char[name_length] }, name_size_{ name_length }, level_{ 1 },
												  health_{ 100 }, xp_{}, accuracy_{ 50 }, evasion_{ 30 }, layer_number_{ 1 },
												  room_number_{ 1 }
	{
		for (size_t i = 0; i < name_size_; i++)
		{
			name_[i] = name[i];
		}
	}

	~Hero()
	{
		delete[] name_;
	}

	char* get_name() const;
	int get_level() const;
	int get_health() const;
	int get_xp() const;
	int get_accuracy() const;
	int get_evasion() const;
	int get_layer_number() const;
	int get_room_number() const;

	void level_up();
	void decrease_health(int amount);
	void increase_health(int amount);
	void add_xp(int amount);
	void add_accuracy(int amount);
	void add_evasion(int amount);
	void set_layer_number(int number);
	void set_room_number(int number);

	void print_hero_info() const;
};

