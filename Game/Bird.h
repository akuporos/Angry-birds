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

	int num_frame = 0;
	const int frame_height = 29;
	const int frame_width = 42;
	float dimbody_x = 0;
	float dimbody_y = 0;
	float bird_x_offset = 0;
	float bird_y_offset = 0;
	sf::Sprite sprite;
	
	b2Body* body = 0;

	bool mouse_press = false;

	float atang = 0;
	float dist = 0;
	float max_length = 50.0;
	clock_t time = 0;
	clock_t time_to_destroy = 1e9;
	bool flag = true;
	bool destroy = false;
	bool flag_fly = false;
	void launch();
public:
	Bird(sf::Texture& bird, b2World& world_, float dimbody_x_, float dimbody_y_);
	void update();
	void voice_manage(std::vector<std::string>& words);
	void event_handle(sf::Vector2i& mouse_coords, sf::Event& event);
	void draw(sf::RenderWindow & window);
	bool get_destroy_flag();
	~Bird();
};

