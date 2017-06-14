#pragma once

#include "Bird.h"
#include "Pig.h"
#include "Plank.h"
#include <list>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>
class Level
{
	b2World& world;
	sf::Texture bird;
	std::queue <Bird> birds;
	std::deque <Bird> birds_stay;
	sf::Texture plank1;
	std::list<Plank> planks;
	sf::Texture pig;
	std::list<Pig> pigs;

	int num_of_pig = 0;
	std::vector<std::vector<int>> pigs_coord;
	std::string pig_icon;
	int num_of_birds = 0;
	std::string bird_icon;
	float bird_dimbody_x = 0;
	float bird_dimbody_y = 0;
	int num_of_houses = 0;
	std::vector<std::vector<int>> coord_of_houses;

	int x = 0;
	int y = 0;
	bool flag_level = false;
	bool next_level = false;
public:
	void load(std::ifstream& fin);
	Level(b2World & world_);
	void make();
	void update();
	void event_handler(sf::Vector2i & mouse_coords, sf::Event & event);
	void voice_manage(std::vector<std::string>& words);
	void draw(sf::RenderWindow& window);
	bool get_level_flag();
	bool get_next_level();
	~Level();
};

