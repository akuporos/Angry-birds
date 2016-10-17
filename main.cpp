#include <SFML/Graphics.hpp>
#include <iostream>
#include <Box2D\Box2D.h>
#include "Bird.h"
#include "Pig.h"
#include "Plunk.h"
#include "Common.h"
#include "ContactListener.h"
#include <list>
void main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 576), "Game");
	window.setFramerateLimit(60);
	sf::Event event;

	b2Vec2 gravity(0.0f, 10.0f);
	b2World world(gravity);
	world.SetContactListener(new ContactListener);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f / common::met_to_pix, 400.0f / common::met_to_pix);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(1024.0f / common::met_to_pix, 10.0f / common::met_to_pix);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	groundBody->CreateFixture(&groundBox, 0.0f);

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	sf::Texture background;
	sf::Sprite sprite_back;
	background.loadFromFile("fon.png");
	sprite_back.setTexture(background);
	sprite_back.setPosition(0, 0);
	
	sf::Texture catapult;
	sf::Sprite sprite_catapult;
	catapult.loadFromFile("catapult.png");
	sprite_catapult.setTexture(catapult);
	sprite_catapult.setPosition(150, 300);

	Bird bird_A("bA.png", world);
	Plunk plunk("plank1.png", world);

	std::list<Pig> pigs;
	pigs.emplace_back("pigs45.png", world);

	while (window.isOpen())
	{
		world.Step(timeStep,velocityIterations,positionIterations);
		
		bird_A.update();

		auto iter = pigs.begin();
		for (iter; iter != pigs.end(); iter++)
		{
			Pig& pig = *iter;
			if (pig.is_alive())
				pig.update();
			else
				iter = pigs.erase(iter);
			if (iter == pigs.end()) break;
		}
		
		plunk.update();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
			bird_A.event_handle(sf::Mouse::getPosition(window), event);
		}
		window.clear();
		window.draw(sprite_back);
		window.draw(sprite_catapult);
		bird_A.draw(window);
		plunk.draw(window);
		for(Pig& pig : pigs)
			pig.draw(window);
		window.display();
	}
}

