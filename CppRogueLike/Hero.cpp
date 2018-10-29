#include "Hero.h"
#include <iostream>
#include "Utilities.h"

char* Hero::get_name() const
{
	return name_;
}

void Hero::create_name(const char name[], int length)
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
		std::cerr << "bad_alloc caught when creating hero name: " << ba.what() << "\n";
	}
}

int Hero::get_level() const
{
	return level_;
}

int Hero::get_health() const
{
	return health_;
}

int Hero::get_max_health() const
{
	return max_health_;
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

int Hero::get_layer_number() const
{
	return layer_number_;
}

int Hero::get_room_number() const
{
	return  room_number_;
}

int Hero::get_grenade_damage() const
{
	return grenade_damage_;
}

int Hero::deal_damage() const
{
	if (!has_sword())
		return 2;
	return 10;
}

bool Hero::has_head_armor() const
{
	return head_armor_;
}

bool Hero::has_chest_armor() const
{
	return chest_armor_;
}

bool Hero::has_sword() const
{
	return sword_;
}

bool Hero::has_healing_potion() const
{
	return healing_potion_ != nullptr;
}

int Hero::grenade_count() const
{
	return grenade_count_;
}

void Hero::equip_head_armor()
{
	head_armor_ = true;
}

void Hero::equip_chest_armor()
{
	chest_armor_ = true;
}

void Hero::equip_sword()
{
	sword_ = true;
}

void Hero::equip_healing_potion()
{
	try 
	{
		healing_potion_ = new Health_Potion();
	}
	catch (std::bad_alloc & ba)
	{
		std::cerr << "bad_alloc caught when equipping health potion: " << ba.what() << "\n";
	}
}

void Hero::use_health_potion()
{
	if(healing_potion_ != nullptr)
	{
		std::cout << "Je hero drinkt een genezingsdrankje en krijgt er " << healing_potion_->get_health() << " levenspunten bij.\n\n";
		increase_health(healing_potion_->get_health());
		delete healing_potion_;
		healing_potion_ = nullptr;
	}
}

void Hero::add_grenade()
{
	grenade_count_ += 1;
}

void Hero::remove_grenade()
{
	grenade_count_ -= 1;
}

void Hero::rest()
{
	increase_health(10);
	std::cout << "Je hero gaat even rustig liggen, sluit zijn ogen en krijgt 10 levenspunten terug.\n\n";
}

void Hero::level_up()
{
	bool not_leveled{ true };
	std::cout << "Je bent een level omhoog!\n\n";

	while (not_leveled) {
		std::cout << "Welke eigenschap wil je verhogen?\n\n";
		std::cout << "[max levens, aanval, verdediging]\n\nActie: ";

		char action_name[15]{};
		std::cin.getline(action_name, 15);

		if (Utilities::are_equal(action_name, "max levens"))
		{
			max_health_ += 50;
			not_leveled = false;
		}
		else if (Utilities::are_equal(action_name, "aanval"))
		{
			accuracy_ += 3;
			not_leveled = false;
		}
		else if (Utilities::are_equal(action_name, "verdediging"))
		{
			evasion_ += 2;
			not_leveled = false;
		}
		else
		{
			std::cout << "Geen geldige actie. Probeer opnieuw(press Enter).\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
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
	if(health_ >= max_health_)
	{
		health_ = max_health_;
	}
}

void Hero::add_xp(int amount)
{
	xp_ += amount;
	if(xp_ > 100)
	{
		xp_ = 100;
	}

	const int previous_level = level_;
	level_ = xp_ / 10;
	if (level_ == 0)
		level_ = 1;
	const int current_level = level_;
	const int difference = current_level - previous_level;
	
	if (difference >= 1)
	{
		for (int i = 0;i < difference; i++)
		{
			level_up();
		}
	}
}

void Hero::add_accuracy(int amount)
{
	accuracy_ += amount;
}

void Hero::add_evasion(int amount)
{
	evasion_ += amount;
}

void Hero::set_layer_number(int number)
{
	layer_number_ = number;
}

void Hero::set_room_number(int number)
{
	room_number_ = number;
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
	std::cout << "evasion: " << evasion_ << "\n\n";
}

void Hero::print_hero_inventory() const
{
	std::cout << "Je hero heeft ";
	if(!has_head_armor() && !has_chest_armor() && !has_sword() && !has_healing_potion() && grenade_count() == 0)
	{
		std::cout << "niks.\n\n";
	}
	else
	{
		if (has_head_armor())
			std::cout << "een helm; ";
		if (has_chest_armor())
			std::cout << "een pantser; ";
		if (has_sword())
			std::cout << "een zwaard; ";
		if (has_healing_potion())
			std::cout << "een genezingsdrankje; ";
		if (grenade_count() != 0)
			std::cout << grenade_count() << " granaten;";
		std::cout << "\n\n";
	}
}
