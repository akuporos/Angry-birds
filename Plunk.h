#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include <string>
#include "Common.h"
#include "Damagable.h"

class Plunk
{
	b2World& world;

	sf::Texture plank1;
	sf::Sprite sprite_planks[4];
	b2Body* body_plank[4];
public:
	Plunk(std::string str, b2World& world_);

	void update();

	void draw(sf::RenderWindow & window);
	
};

