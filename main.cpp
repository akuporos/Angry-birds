#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D\Box2D.h>
#include "Common.h"
#include "ContactListener.h"
#include <list>
#include "Level.h"
#include "Menu.h"
#include <vector>

void main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 512), "Angry birds");
	window.setFramerateLimit(60);
	sf::Event event;

	sf::Music music;
	if (!music.openFromFile("Angry.ogg"))
		std::cout << "bla";
	music.setLoop(true);
	music.play();

	menu(window, event);

	b2Vec2 gravity(0.0f, 10.0f);
	b2World world(gravity);
	world.SetContactListener(new ContactListener);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f / common::met_to_pix, 430.0f / common::met_to_pix);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(1024.0f / common::met_to_pix, 10.0f / common::met_to_pix);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
	groundBody->CreateFixture(&groundBox, 0.0f);

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	sf::Texture background;
	sf::Sprite sprite_back;
	background.loadFromFile("back.png");
	sprite_back.setTexture(background);
	sprite_back.setPosition(0, 0);

	sf::Texture button_pause;
	sf::Sprite sprite_pause;
	button_pause.loadFromFile("pause.png");
	sprite_pause.setTexture(button_pause);
	sprite_pause.setPosition(5, 2);

	sf::Texture button_restart;
	sf::Sprite sprite_restart;
	button_restart.loadFromFile("restart.png");
	sprite_restart.setTexture(button_restart);
	sprite_restart.setPosition(50, 2);

	sf::Texture catapult;
	sf::Sprite sprite_catapult;
	catapult.loadFromFile("rogA1.png");
	sprite_catapult.setTexture(catapult);
	sprite_catapult.setPosition(140, 258);

	sf::Texture catapult1;
	sf::Sprite sprite_catapult1;
	catapult1.loadFromFile("rogB1.png");
	sprite_catapult1.setTexture(catapult1);
	sprite_catapult1.setPosition(142, 261);
	
	int num_of_pig = 3;
	std::vector<std::vector<int>> pigs_coord(num_of_pig, std::vector<int> (2));
	pigs_coord[0][0] = 800;
	pigs_coord[0][1] = 390;
	pigs_coord[1][0] = 500;
	pigs_coord[1][1] = 390;
	pigs_coord[2][0] = 800;
	pigs_coord[2][1] = 290;

	int num_of_birds = 3;
	float bird_dimbody_x = 170;
	float bird_dimbody_y = 300;

	std::list<Level> levels;
	levels.emplace_back(num_of_birds, bird_dimbody_x, bird_dimbody_y, num_of_pig, pigs_coord,world);
	
	sf::Font font;
	font.loadFromFile("FORTE.TTF");
	sf::Text text1;
	
	bool mousepress = false;
	int game_button = 0;
	bool pause_flag = false;

	b2Body* body = 0;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(1023 / common::met_to_pix, 420 / common::met_to_pix);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(2 / common::met_to_pix, 10 / common::met_to_pix);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.01f;
	fixtureDef.friction = 1.0f;

	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	b2Body* body1 = 0;
	b2BodyDef bodyDef1;
	bodyDef1.type = b2_staticBody;
	bodyDef1.position.Set(300 / common::met_to_pix, 420 / common::met_to_pix);

	//body1 = world.CreateBody(&bodyDef1);
	//body1->CreateFixture(&fixtureDef);
	bool level_flag = true;
	while (window.isOpen())
	{
	
		if (game_button != 1)
		{
			world.Step(timeStep, velocityIterations, positionIterations);
			levels.front().update();
		}
		if(game_button == 1)
		{
			text1.setFont(font);
			text1.setFillColor(sf::Color::Yellow);
			text1.setString("Pause");
			text1.setCharacterSize(80);
			text1.setPosition(350, 100);
		}
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (sf::IntRect(5, 2, button_pause.getSize().x, button_pause.getSize().y).contains(sf::Mouse::getPosition(window)))
				{	//нажатие на паузу
					if (!pause_flag) //останавливаем игру
					{
						game_button = 1;
						pause_flag = true;
					}
					else   //продолжаем игру
					{
						game_button = 0;
						pause_flag = false;
					}
					mousepress = true;
				}
				//рестарт игры
				if (sf::IntRect(50, 2, button_restart.getSize().x, button_restart.getSize().y).contains(sf::Mouse::getPosition(window)))
				{
					game_button = 2;
					mousepress = true;
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (game_button == 1)
				{
					mousepress = false;
				}
				if (game_button == 2)
				{
					
					mousepress = false;
				}
				break;
			}
			levels.front().event_handler(sf::Mouse::getPosition(window), event);
		}
		window.clear();
		window.draw(sprite_back);
		window.draw(sprite_pause);
		if (game_button == 1) window.draw(text1);
		window.draw(sprite_restart);
		window.draw(sprite_catapult);
		levels.front().draw(window);
		window.draw(sprite_catapult1);
		window.display();
	}
}

