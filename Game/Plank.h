#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include <string>
#include "Common.h"
#include "Damagable.h"

class Plank : public Damagable
{
	b2World& world;

	sf::Sprite sprite_plank;
	b2Body* body_plank;

public:
	Plank(sf::Texture& planka1, int x, int y, int angle, b2World& world_);
	void update();
	void draw(sf::RenderWindow & window);
	void damage(int hp);
	~Plank();
	
};

