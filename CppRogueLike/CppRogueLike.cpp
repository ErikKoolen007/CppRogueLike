// CppRogueLike.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <crtdbg.h>
#include "Dungeon.h"
#include "Hero.h"
#include <locale>
#include "Utilities.h"
#include "Monster.h"
#include <fstream>
#include "Spawner.h"

void clear_screen()
{
	system("CLS");
}

int ask_number(int min, int max, const char message[])
{
	clear_screen();
	int width{};

	while (true)
	{
		std::cout << "Geef een waarde tussen de " << min << " en " << max << " voor de " << message << " van de dungeon: ";

		if (!(std::cin >> width))
		{
			std::cout << "Geen numerieke waarde!\n";
		}
		else if (width >= min && width <= max)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			return width;
		}

		std::cout << "Geen waarde tussen de " << min << " en " << max << "!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

size_t ask_name(char* char_name, int hero_name_length)
{
	size_t name_length{};
	
	while (true)
	{
		std::cout << "Geef je hero een naam van maximaal "<< hero_name_length << " karakters: ";

		for (int i = 0; i < hero_name_length; i++)
		{
			name_length = i;
			if (std::cin.peek() == '\n')
			{
				name_length--;
				break;
			}
			std::cin >> char_name[i];
		}

		const char x = std::cin.get();

		if (x != '\n')
		{
			std::cout << "Er zijn meer dan " << hero_name_length << " karakters ingevuld. Probeer opnieuw\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			name_length++;

			return name_length;
		}
	}
}

int main()
{
	bool game_loop{ true };
	bool enemy_alive{ false };
	const int hero_name_length{ 20 };
	const int hero_action_length{ 20 };
	char char_name[hero_name_length]{};
	char action_name[hero_action_length]{};
	Hero* hero = nullptr;

	const int width = ask_number(2, 10, "breedte");
	const int height = ask_number(2, 10, "lengte");
	const int depth = ask_number(2, 10, "diepte");
	
	try 
	{
		hero = new Hero();
	}
	catch (std::bad_alloc & ba)
	{
		std::cerr << "bad_alloc caught when creating hero: " << ba.what() << "\n";
	}
	bool not_done_loading{ true };
	char answer[4];
	while (not_done_loading) {
		std::cout << "Wil je een hero laden?\n\n";
		std::cout << "[ja, nee]\n\nActie: ";
		std::cin.getline(answer, 4);

		if (Utilities::are_equal(answer, "ja"))
		{
			std::ifstream ifs("hero.txt");
			if(isdigit(ifs.narrow(ifs.peek())))
			{
				if (ifs >> *hero)
				{
					std::cout << "Hero succesvol geladen.\n\n";
				}
				not_done_loading = false;
			}
			else
			{
				std::cout << "Kan geen save vinden.\n\n";
				std::cout << "Laten we dan een hero maken.\n\n";
				const size_t name_length = ask_name(char_name, hero_name_length);
				*hero = Hero(char_name, name_length);
				not_done_loading = false;
			}
		}
		else if (Utilities::are_equal(answer, "nee"))
		{
			std::cout << "Laten we dan een hero maken.\n\n";
			const size_t name_length = ask_name(char_name, hero_name_length);
			*hero = Hero(char_name, name_length);
			not_done_loading = false;
		}
		else
		{
			std::cout << "Geen geldige actie. Probeer opnieuw(press Enter).\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	clear_screen();
	Dungeon* dungeon = nullptr;
	Spawner* spawner = nullptr;
	try
	{
		dungeon = new Dungeon{ width, height, depth };
		spawner = new Spawner();
	}
	catch (std::bad_alloc & ba)
	{
		std::cerr << "bad_alloc caught when creating dungeon or spawner: " << ba.what() << "\n";
		game_loop = false;
	}
	
	if(dungeon !=nullptr)
		dungeon->generate_dungeon();
	hero->set_layer_number(1);
	hero->set_room_number(dungeon->get_layer(0)->get_start()->get_number());

	while (game_loop)
	{
		bool hero_escaped = false;
		bool is_boss_fight;
		Utilities::print_room_description(*dungeon, *hero);
		std::cout << "Uitgangen: ";
		Utilities::print_possible_directions(*dungeon, *hero);

		bool did_enemy_spawn = Utilities::did_enemy_spawn();
		Monster* monster = nullptr;

		if (dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_number() == dungeon->get_layer(depth - 1)->get_end()->get_number()
			&& dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_level() == depth)
		{
			did_enemy_spawn = true;
		}

		if(did_enemy_spawn)
		{
			enemy_alive = true;
			if (dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_number() == dungeon->get_layer(depth - 1)->get_end()->get_number()
				&& dungeon->get_layer(hero->get_layer_number() - 1)->get_room(hero->get_room_number() - 1)->get_level() == depth)
			{
				monster = spawner->spawn_random_monster(hero->get_layer_number(), depth, true);
				is_boss_fight = true;
			}
			else
			{
				monster = spawner->spawn_random_monster(hero->get_layer_number(), depth, false);
				is_boss_fight = false;
			}

			while (enemy_alive)
			{
				std::cout << "Je bent in gevecht met een ";
				monster->print_name();
				std::cout << " met " << monster->get_health() << " levens.\n\n";

				std::cout << "Jij hebt " << hero->get_health() << " van de " << hero->get_max_health() << " levenspunten.\n\n";

				bool unchosen_action{ true };
				while (unchosen_action) {

					std::cout << "Wat doe je?\n\n";
					std::cout << "[aanval, vlucht, drink drankje, gebruik granaat]\n\nActie: ";
					std::cin.getline(action_name, hero_action_length);

					if (Utilities::are_equal(action_name, "aanval"))
					{
						if (Utilities::attack_is_hit(hero->get_accuracy(), monster->get_defence()))
						{
							const int damage = hero->deal_damage();
							monster->decrease_health(damage);
							std::cout << damage << " schade toegebracht.\n\n";

							if (monster->get_health() <= 0 && !is_boss_fight)
							{
								std::cout << "Monster verslagen!!!\n\n";
								hero->add_xp(monster->get_level());
								spawner->destroy_monster();
								monster = nullptr;
								enemy_alive = false;
							}
							else if (monster->get_health() <= 0 && is_boss_fight)
							{
								std::cout << "Baas verslagen!!!\n\n";
								hero->add_xp(monster->get_level());
								spawner->destroy_monster();
								monster = nullptr;
								enemy_alive = false;
								hero_escaped = true;
								game_loop = false;
								std::cout << "Je hebt de game gewonnen!\n\n";
							}
						}
						unchosen_action = false;
					}
					else if (Utilities::are_equal(action_name, "vlucht"))
					{
						std::cout << "\nWelke richting?\n";
						Utilities::print_possible_directions(*dungeon, *hero);
						std::cout << "\n";
						Utilities::move_to_input_direction(*dungeon, *hero);

						spawner->destroy_monster();
						monster = nullptr;
						enemy_alive = false;
						hero_escaped = true;
						unchosen_action = false;
					}
					else if (Utilities::are_equal(action_name, "drink drankje"))
					{
						if (hero->has_healing_potion())
						{
							hero->use_health_potion();
							unchosen_action = false;
						}
						else
						{
							std::cout << "Je hebt geen genezingsdrankje.\n\n";
						}
					}
					else if (Utilities::are_equal(action_name, "gebruik granaat"))
					{
						if (hero->grenade_count() >= 1)
						{
							hero->remove_grenade();
							const int damage = hero->get_grenade_damage();
							monster->decrease_health(damage);
							std::cout << "Je hebt een granaat gegooid en " << damage << " schade toegebracht.\n\n";

							if (monster->get_health() <= 0 && !is_boss_fight)
							{
								std::cout << "Monster verslagen!!!\n\n";
								hero->add_xp(monster->get_level());
								spawner->destroy_monster();
								monster = nullptr;
								enemy_alive = false;
							}
							else if (monster->get_health() <= 0 && is_boss_fight)
							{
								std::cout << "Baas verslagen!!!\n\n";
								hero->add_xp(monster->get_level());
								spawner->destroy_monster();
								monster = nullptr;
								enemy_alive = false;
								hero_escaped = true;
								game_loop = false;
								std::cout << "Je hebt de game gewonnen!\n\n";
							}
							unchosen_action = false;
						}
						else
						{
							std::cout << "Je hebt geen granaat!\n\n";
						}
					}
					else
					{
						std::cout << "Geen geldige actie. Probeer opnieuw(press Enter).\n";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}
				}

				if (monster != nullptr) {
					//Enemy attack
					std::cout << "Vijand valt aan!\n\n";
					if (Utilities::attack_is_hit(monster->get_accuracy(), hero->get_evasion()))
					{
						for (int i = 0; i < monster->get_attack_amount(); i++)
						{
							const int damage = monster->deal_damage();
							hero->decrease_health(damage);
							std::cout << damage << " schade toegebracht.\n\n";
						}

						if (hero->get_health() <= 0)
						{
							std::cout << "Je bent dood, GAME OVER.\n\n";
							spawner->destroy_monster();
							monster = nullptr;
							enemy_alive = false;
							hero_escaped = true;
							game_loop = false;
						}
					}
				}
			}
		}
		if((!did_enemy_spawn || !enemy_alive) && !hero_escaped)
		{
			bool empty_room_bool{ true };
			
			std::cout << "\nAanwezig: helemaal niemand.\n\n";
			while (empty_room_bool) {
				std::cout << "Wat doe je?\n\n";
				std::cout << "[ga verder, zoek, rust uit, drink drankje, bekijk spullen, bekijk kaart, bekijk hero info, save hero, quit]\n\nActie: ";
				std::cin.getline(action_name, hero_action_length);

				if (Utilities::are_equal(action_name, "ga verder"))
				{
					std::cout << "\nWelke richting?\n";
					Utilities::print_possible_directions(*dungeon, *hero);
					std::cout << "\n";
					Utilities::move_to_input_direction(*dungeon, *hero);

					empty_room_bool = false;
				}
				else if(Utilities::are_equal(action_name, "zoek"))
				{
					Utilities::go_search(*dungeon, *hero);
				}
				else if (Utilities::are_equal(action_name, "rust uit"))
				{
					hero->rest();
					empty_room_bool = false;
				}
				else if (Utilities::are_equal(action_name, "drink drankje"))
				{
					if (hero->has_healing_potion())
					{
						hero->use_health_potion();
					}
					else
					{
						std::cout << "Je hebt geen genezingsdrankje.\n\n";
					}
				}
				else if (Utilities::are_equal(action_name, "bekijk spullen"))
				{
					hero->print_hero_inventory();
				}
				else if (Utilities::are_equal(action_name, "bekijk kaart"))
				{
					dungeon->display_map(hero->get_layer_number(), hero->get_room_number());
				}
				else if (Utilities::are_equal(action_name, "bekijk hero info"))
				{
					hero->print_hero_info();
				}
				else if (Utilities::are_equal(action_name, "save hero"))
				{
					Utilities::save_hero(*hero);
				}
				else if (Utilities::are_equal(action_name, "quit"))
				{
					empty_room_bool = false;
					game_loop = false;
				}
				else if (Utilities::are_equal(action_name, "debug"))
				{
					dungeon->debug_print();
				}
				else
				{
					std::cout << "Geen geldige actie. Probeer opnieuw(press Enter).\n";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}

	delete spawner;
	delete hero;
	delete dungeon;

	//Memory check
	std::cout << "\nMemory leaks? (0 for no, 1 for yes. See output for details.)" << _CrtDumpMemoryLeaks() << std::endl;
}
