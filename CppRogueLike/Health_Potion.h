#pragma once
class Health_Potion
{
	int health_;
public:
	Health_Potion() : health_{ 50 }
	{
	}

	int get_health() const;
};

