#pragma once

#include "Bird.h"
#include "Pig.h"
#include "Plank.h"
#include <list>
#include <queue>
#include <deque>
class Level
{
	b2World& world;
	sf::Font font;
	sf::Text text;
	bool flag = false;
	sf::Texture bird;
	std::queue <Bird> birds;
	std::deque <Bird> birds_stay;
	sf::Texture plank1;
	std::list<Plank> planks;
	sf::Texture pig;
	std::list<Pig> pigs;
	bool flag_level = true;
public:
	Level(int num_of_birds, float dimbody_x, float dimbody_y, int num_of_pig, std::vector<std::vector<int>>& pigs_coord, b2World & world_);
	void update();
	void event_handler(sf::Vector2i & mouse_coords, sf::Event & event);
	void draw(sf::RenderWindow& window);
	bool get_level_flag();
	~Level();
};

