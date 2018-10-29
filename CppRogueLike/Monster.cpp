#include "Monster.h"
#include "Utilities.h"
#include <iostream>

int Monster::get_health() const
{
	return health_;
}

int Monster::get_defence() const
{
	return defence_;
}

int Monster::get_level() const
{
	return level_;
}

int Monster::get_accuracy() const
{
	return accuracy_;
}

int Monster::get_attack_amount() const
{
	return attack_amount_;
}

int Monster::deal_damage() const
{
	return Utilities::get_random(min_damage_, max_damage_);
}

void Monster::decrease_health(int amount)
{
	health_ -= amount;
}

void Monster::create_name(const char name[], int length)
{
	try {
		name_ = new char[length];
		for (int i = 0; i < length; i++)
		{
			name_[i] = name[i];
		}
	}
	catch (std::bad_alloc & ba)
	{
		std::cerr << "bad_alloc caught when creating monster name: " << ba.what() << "\n";
	}
}

void Monster::set_name_size(int size)
{
	name_size_ = size;
}

void Monster::set_level(int level)
{
	level_ = level;
}

void Monster::set_accuracy(int accuracy)
{
	accuracy_ = accuracy;
}

void Monster::set_attack_amount(int attack_amount)
{
	attack_amount_ = attack_amount;
}

void Monster::set_min_damage(int min_dmg)
{
	min_damage_ = min_dmg;
}

void Monster::set_max_damage(int max_dmg)
{
	max_damage_ = max_dmg;
}

void Monster::set_defence(int defence)
{
	defence_ = defence;
}

void Monster::set_health(int health)
{
	health_ = health;
}

void Monster::print_name() const
{
	for (int i = 0; i < name_size_; i++)
	{
		std::cout << name_[i];
	}
}
