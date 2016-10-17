#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D\Box2D.h>
#include <string>
#include <ctime>
#include <algorithm>
#include "Common.h"
class Bird
{
	b2World& world;

	sf::Texture bird;

	int num_frame = 0;
	const int frame_height = 29;
	const int frame_width = 42;
	const float dimbody_x = 170.0f;
	const float dimbody_y = 300.0f;
	sf::Sprite sprite;
	
	b2Body* body = 0;

	bool mouse_press = false;

	float atang = 0;
	float dist = 0;
	float max_length = 50.0;
	clock_t time = 0;
	bool flag = true;
	void launch();
public:
	Bird(std::string str, b2World& world_);
	void update();
	void event_handle(sf::Vector2i& mouse_coords, sf::Event& event);
	void draw(sf::RenderWindow & window);
};

