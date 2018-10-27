#include "Hero.h"
#include <iostream>

char* Hero::get_name() const
{
	return name_;
}

int Hero::get_level() const
{
	return level_;
}

int Hero::get_health() const
{
	return health_;
}

int Hero::get_xp() const
{
	return xp_;
}

int Hero::get_accuracy() const
{
	return accuracy_;
}

int Hero::get_evasion() const
{
	return evasion_;
}

void Hero::level_up()
{
	if(level_ < 10)
		level_ += 1;
}

void Hero::decrease_health(int amount)
{
	health_ -= amount;
	if(health_ < 0)
	{
		health_ = 0;
	}
}

void Hero::increase_health(int amount)
{
	health_ += amount;
}

void Hero::add_xp(int amount)
{
	xp_ += amount;
}

void Hero::add_accuracy(int amount)
{
	accuracy_ += amount;
}

void Hero::add_evasion(int amount)
{
	evasion_ += amount;
}

void Hero::print_hero_info() const
{
	std::cout << "Hero name: ";
	for (size_t i = 0; i < name_size_; i++)
	{
		std::cout << name_[i];
	}
	std::cout << "\n";
	std::cout << "level: " << level_ << "\n";
	std::cout << "health: " << health_ << "\n";
	std::cout << "xp: " << xp_ << "\n";
	std::cout << "accuracy: " << accuracy_ << "\n";
	std::cout << "evasion: " << evasion_ << "\n";
}
