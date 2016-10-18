#include "Level.h"

Level::Level(int num_of_birds, float bird_dimbody_x, float bird_dimbody_y, int num_of_pig, std::vector<std::vector<int>>& pigs_coord, b2World& world_) : world(world_)
{
	bird.loadFromFile("bA.png");	
	for (int i = 0; i<num_of_birds; i++)
		birds.emplace(bird, world, bird_dimbody_x, bird_dimbody_y);
	float stay_x = 130;
	float stay_y = 390;
	for (int i = 0; i < num_of_birds - 1; i++)
	{
		birds_stay.emplace_back(bird, world, stay_x, stay_y);
		stay_x -= 40;
	}

	int x = 800;
	int y = 425;
	
	plank1.loadFromFile("plank.png");
	planks.emplace_back(plank1, x, y, 0, world);
	planks.emplace_back(plank1, x - plank1.getSize().x / 2 + plank1.getSize().y, y - plank1.getSize().y / 2 - plank1.getSize().x / 2, 90, world); //левая
	planks.emplace_back(plank1, x, y - plank1.getSize().y - plank1.getSize().x, 0, world); //Верхняя
	planks.emplace_back(plank1, x + plank1.getSize().x / 2 - plank1.getSize().y, y - plank1.getSize().y / 2 - plank1.getSize().x / 2, 90, world);	//правая

	pig.loadFromFile("pigs45.png");
	for (int i = 0; i < num_of_pig; i++)
	{
		pigs.emplace_back(pig, world, pigs_coord[i][0], pigs_coord[i][1]);
	}
	font.loadFromFile("FORTE.TTF");
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
			text.setFont(font);
			text.setFillColor(sf::Color::Yellow);
			text.setString("Game over");
			text.setCharacterSize(80);
			text.setPosition(350, 100);
			flag = true;
		}
		auto iter1 = planks.begin();
		for (iter1; iter1 != planks.end(); iter1++)
		{
			Plank& plank = (*iter1);
			if (plank.is_alive())
				plank.update();
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
	if (flag) 
		window.draw(text);
}

bool Level::get_level_flag()
{
	return flag_level;
}

Level::~Level()
{
	flag_level = false;
}

