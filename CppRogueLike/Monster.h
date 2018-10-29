#pragma once

class Monster
{
	char* name_;
	int name_size_;
	int level_;
	int accuracy_;
	int attack_amount_;
	int min_damage_;
	int max_damage_;
	int defence_;
	int health_;
public:
	Monster() : name_(nullptr)
	{
	}
	~Monster()
	{
		delete[] name_;
	}

	int get_health() const;
	int get_defence() const;
	int get_level() const;
	int get_accuracy() const;
	int get_attack_amount() const;
	int deal_damage() const;

	void decrease_health(int amount);
	void create_name(const char name[], int length);
	void set_name_size(int size);
	void set_level(int level);
	void set_accuracy(int accuracy);
	void set_attack_amount(int attack_amount);
	void set_min_damage(int min_dmg);
	void set_max_damage(int max_dmg);
	void set_defence(int defence);
	void set_health(int health);
	void print_name() const;
};

