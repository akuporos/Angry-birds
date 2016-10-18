#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include <ctime>
#include <iostream>
#include "Common.h"
#include "Damagable.h"

class Pig : public Damagable
{
	b2World& world;

	sf::Sprite sprite;

	int num_frame_x = 0;
	int num_frame_y = 0;
	const int frame_height = 45;
	const int frame_width = 44;
	float dimbody_x = 0;
	float dimbody_y = 0;

	b2Body* body = 0;

	clock_t time = 0;

	const int hp1 = 500;
	const int hp2 = 1000;
	const int hp3 = 2000;
public:
	Pig(sf::Texture& pig, b2World& world, float pig_dimbody_x, float pig_dimbody_y);
	void update();
	void draw(sf::RenderWindow & window);
	void damage(int hp);
	~Pig();
};

