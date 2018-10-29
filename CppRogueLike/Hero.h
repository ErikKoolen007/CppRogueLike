#pragma once
#include "Health_Potion.h"
#include <ostream>
#include <istream>

class Hero
{
	char* name_;
	size_t name_size_;
	int level_;
	int health_;
	int max_health_;
	int xp_;
	int accuracy_;
	int evasion_;
	int layer_number_;
	int room_number_;

	bool head_armor_;
	bool chest_armor_;
	bool sword_;
	Health_Potion* healing_potion_;
	int grenade_count_;
	int grenade_damage_;

public:
	Hero(): name_(nullptr), name_size_(0), level_(1), health_(0), max_health_(0), xp_(0), accuracy_(0), evasion_(0),
	        layer_number_(0), room_number_(0), head_armor_(false), chest_armor_(false), sword_(false),
	        healing_potion_(nullptr), grenade_count_(0), grenade_damage_(0)
	{
	}

	Hero(const char name[], size_t name_length) : name_{new char[name_length]}, name_size_{name_length}, level_{1},
	                                              health_{100}, max_health_{100}, xp_{}, accuracy_{50}, evasion_{30},
	                                              layer_number_{1},
	                                              room_number_{1}, head_armor_{false}, chest_armor_{false},
	                                              sword_{false}, healing_potion_{nullptr}, grenade_count_{ 5 },
	                                              grenade_damage_{ 100 }
	{
		for (size_t i = 0; i < name_size_; i++)
		{
			name_[i] = name[i];
		}
	}

	~Hero()
	{
		delete[] healing_potion_;
		delete[] name_;
	}

	Hero &operator=(Hero &&h) noexcept
	{
		if (&h == this)
			return *this;

		delete[] healing_potion_;
		delete[] name_;

		name_ = h.name_;
		name_size_ = h.name_size_;
		level_ = h.level_;
		health_ = h.health_;
		max_health_ = h.max_health_;
		xp_ = h.xp_;
		accuracy_ = h.accuracy_;
		evasion_ = h.evasion_;
		layer_number_ = h.layer_number_;
		room_number_ = h.room_number_;

		head_armor_ = h.head_armor_;
		chest_armor_ = h.chest_armor_;
		sword_ = h.sword_;
		healing_potion_ = h.healing_potion_;
		grenade_count_ = h.grenade_count_;
		grenade_damage_ = h.grenade_damage_;

		h.name_ = nullptr;
		h.healing_potion_ = nullptr;
		h.name_size_ = h.level_ = h.health_ = h.max_health_ = h.xp_ =
			h.accuracy_ = h.evasion_ = h.layer_number_ = h.room_number_ = h.grenade_count_ = h.grenade_damage_ = 0;
		h.head_armor_ = h.chest_armor_ = h.sword_ = false;

		return *this;
	}

	char* get_name() const;
	void create_name(const char name[], int length);
	int get_level() const;
	int get_health() const;
	int get_max_health() const;
	int get_xp() const;
	int get_accuracy() const;
	int get_evasion() const;
	int get_layer_number() const;
	int get_room_number() const;
	int get_grenade_damage() const;
	int deal_damage() const;

	bool has_head_armor() const;
	bool has_chest_armor() const;
	bool has_sword() const;
	bool has_healing_potion() const;
	int grenade_count() const;
	void equip_head_armor();
	void equip_chest_armor();
	void equip_sword();
	void equip_healing_potion();
	void use_health_potion();
	void add_grenade();
	void remove_grenade();
	void rest();
	void level_up();
	void decrease_health(int amount);
	void increase_health(int amount);
	void add_xp(int amount);
	void add_accuracy(int amount);
	void add_evasion(int amount);
	void set_layer_number(int number);
	void set_room_number(int number);

	void print_hero_info() const;
	void print_hero_inventory() const;

	friend std::ostream& operator<<(std::ostream& os, const Hero& h)
	{
		os << h.name_size_ << '\n';
		for(size_t i = 0; i < h.name_size_; i++)
		{
			os << h.name_[i];
		}
		os << '\n';
		os << h.level_ << '\n';
		os << h.health_ << '\n';
		os << h.max_health_ << '\n';
		os << h.xp_ << '\n';
		os << h.accuracy_ << '\n';
		os << h.evasion_ << '\n';
		os << h.head_armor_ << '\n';
		os << h.chest_armor_ << '\n';
		os << h.sword_ << '\n';
		os << h.has_healing_potion() << '\n';
		os << h.grenade_count_ << '\n';

		return os;
	}

	friend std::istream& operator>>(std::istream& is, Hero& h)
	{
		char buffer[20];
		bool has_healing_potion;
		is >> h.name_size_;
		for (size_t i = 0; i < h.name_size_; i++)
		{
			if (is.peek() == is.narrow(' '))
			{
				buffer[i] = ' ';
				is.ignore(1);
			}
			else
			{
				is >> buffer[i];
			}
		}
		h.create_name(buffer, h.name_size_);
		is >> h.level_ >> h.health_ >> h.max_health_ >> h.xp_ >> h.accuracy_ >> h.evasion_ >>
			h.head_armor_ >> h.chest_armor_ >> h.sword_ >> has_healing_potion >> h.grenade_count_;

		if(has_healing_potion)
		{
			h.equip_healing_potion();
		}
		else
		{
			h.healing_potion_ = nullptr;
		}
		h.grenade_damage_ = 100;

		return is;
	}
};

