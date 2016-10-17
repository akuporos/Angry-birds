#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include <string>
#include <ctime>
#include <iostream>
#include "Common.h"
#include "Damagable.h"

class Pig : public Damagable
{
	b2World& world;

	sf::Texture pig;
	sf::Sprite sprite;

	int num_frame_x = 0;
	int num_frame_y = 0;
	const int frame_height = 45;
	const int frame_width = 44;
	const float dimbody_x = 800;
	const float dimbody_y = 374;

	b2Body* body = 0;

	clock_t time = 0;

	const int hp1 = 1500;
	const int hp2 = 2500;
	const int hp3 = 4000;
public:
	Pig(std::string str, b2World& world);
	void update();
	void draw(sf::RenderWindow & window);
	void damage(int hp);
	~Pig();
};

