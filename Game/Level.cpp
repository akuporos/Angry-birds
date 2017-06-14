#include "Level.h"

void Level::load(std::ifstream& fin)
{
	fin >> num_of_pig;
	fin >> pig_icon;
	pigs_coord.resize(num_of_pig);
	for (int i = 0; i < pigs_coord.size(); i++)
		pigs_coord[i].resize(2);
	for (int i = 0; i < num_of_pig; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			fin >> pigs_coord[i][j];
		}
	}
	fin >> num_of_birds;
	fin >> bird_icon;
	fin >> bird_dimbody_x;
	fin >> bird_dimbody_y;
	fin >> num_of_houses;
	coord_of_houses.resize(num_of_houses);
	for (int i = 0; i < coord_of_houses.size(); i++)
		coord_of_houses[i].resize(2);
	for (int i = 0; i < num_of_houses; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			fin >> coord_of_houses[i][j];
		}
	}
}

Level::Level(b2World& world_) : world(world_)
{
	
}

void Level::make()
{
	bird.loadFromFile(bird_icon);
	for (int i = 0; i<num_of_birds; i++)
		birds.emplace(bird, world, bird_dimbody_x, bird_dimbody_y);
	float stay_x = 130;
	float stay_y = 390;
	for (int i = 0; i < num_of_birds - 1; i++)
	{
		birds_stay.emplace_back(bird, world, stay_x, stay_y);
		stay_x -= 40;
	}

	plank1.loadFromFile("picture/plank3.png");
	for (int i = 0; i < num_of_houses; i++)
	{
		x = coord_of_houses[i][0];
		y = coord_of_houses[i][1];
		planks.emplace_back(plank1, x, y, 0, world);
		planks.emplace_back(plank1, x - plank1.getSize().x / 2 + plank1.getSize().y / 2, y - plank1.getSize().x / 2 - plank1.getSize().y, 90, world); //левая
		planks.emplace_back(plank1, x, y - plank1.getSize().y - plank1.getSize().x, 0, world); //Верхняя
		planks.emplace_back(plank1, x + plank1.getSize().x / 2 - plank1.getSize().y / 2, y - plank1.getSize().x / 2 - plank1.getSize().y, 90, world);	//правая
	}
	pig.loadFromFile(pig_icon);
	for (int i = 0; i < num_of_pig; i++)
	{
		pigs.emplace_back(pig, world, pigs_coord[i][0], pigs_coord[i][1]);
	}
}

void Level::update()
{
	
		auto iter = pigs.begin();
		for (iter; iter != pigs.end();)
		{
			Pig& pig = *iter;
			if (pig.is_alive())
			{
				pig.update();
				iter++;
			}
			else
			{
				iter = pigs.erase(iter);
			}
		}


		if (!birds.empty())
			birds.front().update();
		for (int i = 0; i < birds_stay.size(); i++)
		{
			birds_stay[i].update();
		}

		if (!birds.empty() && birds.front().get_destroy_flag())
		{
			birds.pop();
			if (!birds_stay.empty())
				birds_stay.pop_back();
		}
		if (!pigs.empty() && birds.empty())
		{
			flag_level = true;
		}
		if (pigs.empty())
		{
			next_level = true;
		}
		auto iter1 = planks.begin();
		for (iter1; iter1 != planks.end();)
		{
			Plank& plank = (*iter1);
			if (plank.is_alive())
			{
				plank.update();
				iter1++;
			}
			else
			{
				iter1 = planks.erase(iter1);
				if (iter1 == planks.end()) break;
			}
		}
	
}

void Level::event_handler(sf::Vector2i& mouse_coords, sf::Event& event)
{
	if(!birds.empty())
		birds.front().event_handle(mouse_coords, event);
}

void Level::voice_manage(std::vector<std::string>& words)
{
	if (!birds.empty())
		birds.front().voice_manage(words);
}

void Level::draw(sf::RenderWindow& window)
{
	if(!birds.empty())
		birds.front().draw(window);
	for (int i = 0; i < birds_stay.size(); i++)
	{
		birds_stay[i].draw(window);
	}
	for (Plank& plank : planks)
		plank.draw(window);
	for (Pig& pig : pigs)
		pig.draw(window);
}

bool Level::get_level_flag()
{
	return flag_level;
}

bool Level::get_next_level()
{
	return next_level;
}

Level::~Level()
{
	
}

