#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D\Box2D.h>
#include "Common.h"
#include "ContactListener.h"
#include "Level.h"
#include "VoiceManage.h"
#include "Menu.h"
#include <vector>
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>

void main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 512), "Angry birds");
	window.setFramerateLimit(60);
	sf::Event event;

	int volume = 100;
	sf::Music music;
	if (!music.openFromFile("Angry.ogg"))
		std::cout << "bla";
	music.setLoop(true);
	music.setVolume(volume);
	//music.play();
	
	bool flag_menu = false;

	Menu* menu = 0;
	menu = new Menu(flag_menu);
	menu->event_handler(window, event);
	menu->draw(window);

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
	background.loadFromFile("picture/back.png");
	sprite_back.setTexture(background);
	sprite_back.setPosition(0, 0);

	sf::Texture button_pause;
	sf::Sprite sprite_pause;
	button_pause.loadFromFile("picture/pause1.png");
	sprite_pause.setTexture(button_pause);
	sprite_pause.setPosition(5, 2);

	sf::Texture button_play;
	sf::Sprite sprite_play;

	sf::Texture button_restart;
	sf::Sprite sprite_restart;
	button_restart.loadFromFile("picture/Restart1.png");
	sprite_restart.setTexture(button_restart);
	sprite_restart.setPosition(50, 2);

	sf::Texture catapult;
	sf::Sprite sprite_catapult;
	catapult.loadFromFile("picture/rogA1.png");
	sprite_catapult.setTexture(catapult);
	sprite_catapult.setPosition(140, 258);

	sf::Texture catapult1;
	sf::Sprite sprite_catapult1;
	catapult1.loadFromFile("picture/rogB1.png");
	sprite_catapult1.setTexture(catapult1);
	sprite_catapult1.setPosition(142, 261);

	std::ifstream* lvl1 = 0;
	lvl1 = new std::ifstream("levels/lev1.txt");

	Level* level1 = 0;
	level1 = new Level(world);
	level1->load(*lvl1);
	level1->make();
	lvl1->seekg(0, std::ios::beg);

	sf::Font font;
	font.loadFromFile("FORTE.TTF");
	sf::Text text1, text;

	bool mousepress = false;
	int game_button = 0;
	bool pause_flag = false;
	bool flag = false;

	b2Body* body = 0;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(1023 / common::met_to_pix, 420 / common::met_to_pix);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1 / common::met_to_pix, 420 / common::met_to_pix);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);

	b2Body* body1 = 0;
	b2BodyDef bodyDef1;
	bodyDef1.type = b2_staticBody;
	bodyDef1.position.Set(258 / common::met_to_pix, 420 / common::met_to_pix);
	b2PolygonShape dynamicBox1;
	dynamicBox1.SetAsBox(2 / common::met_to_pix, 20 / common::met_to_pix);
	b2FixtureDef fixtureDef1;
	fixtureDef1.shape = &dynamicBox1;
	body1 = world.CreateBody(&bodyDef1);
	body1->CreateFixture(&fixtureDef1);

	bool level_flag = true;
	clock_t time_to_restart = 10e9;
	clock_t voice_time = 10e9;
	std::string  level_name = "levels/lev1.txt";
	bool game_over = false;
	
	VoiceManage voice;
	bool manage_by_voice = false;
	voice.send_request();
	voice_time = clock();
	while (window.isOpen())
	{
		
		if (game_button != 1 && !game_over) //если не нажата пауза
		{
			world.Step(timeStep, velocityIterations, positionIterations);
			level1->update();
			if (level1->get_level_flag() && !flag) //если продул уровень
			{
				time_to_restart = clock();
				text.setFont(font);
				text.setFillColor(sf::Color::Yellow);
				text.setString("Game over");
				text.setCharacterSize(80);
				text.setPosition(350, 100);
				flag = true;
			}
			if (clock() - time_to_restart >= 3000 && flag) // перезапуск уровня если продул
			{
				flag = false;
				delete  level1;
				level1 = new Level(world);
				level1->load(*lvl1);
				level1->make();
				lvl1->seekg(0, std::ios::beg);
				voice_time = clock();
			}
			if (level1->get_next_level() && !game_over) //переход на следующий уровень
			{
				lvl1->close();
				level_name[10]++;
				lvl1 = new std::ifstream(level_name);
				if (lvl1->is_open())
				{
					delete  level1;
					level1 = new Level(world);
					level1->load(*lvl1);
					level1->make();
					lvl1->seekg(0, std::ios::beg);
				}
				else
				{
					game_over = true;
				}
				voice_time = clock();
			}
		}
		//пауза
		if (game_button == 1)
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
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Q:
				{
					int vi = volume;
					if (vi - 10 >= 0) vi -= 5;
					else vi = 0;
					music.setVolume(vi);
					volume = vi;
					break;
				}
				case sf::Keyboard::W:
				{
					int vj = volume;
					if (vj + 10 <= 100) vj += 5;
					else vj = 100;
					music.setVolume(vj);
					volume = vj;
					break;
				}
				case sf::Keyboard::Escape:
				{
					flag_menu = true;
					Menu* menu = 0;
					menu = new Menu(flag_menu);
					menu->event_handler(window, event);

				}
				case sf::Keyboard::N:
				{
					manage_by_voice = true;
				}
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (sf::IntRect(5, 2, button_pause.getSize().x, button_pause.getSize().y).contains(sf::Mouse::getPosition(window)))
				{	//нажатие на паузу
					if (!pause_flag) //останавливаем игру
					{
						game_button = 1;
						button_play.loadFromFile("picture/play.png");
						sprite_play.setTexture(button_play);
						sprite_play.setPosition(5, 2);

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
					delete  level1;
					level1 = new Level(world);
					level1->load(*lvl1);
					level1->make();
					lvl1->seekg(0, std::ios::beg);
					game_button = 0;
					flag = false;
					mousepress = false;
				}
				break;
			}
			if (!manage_by_voice)
			{
				level1->event_handler(sf::Mouse::getPosition(window), event);
			}
		}
		//if (clock() - voice_time >= 1000)
		if (manage_by_voice && (clock() - voice_time >= 3000))
		{
			std::vector<std::string> words = voice.new_audio();
			level1->voice_manage(words);
			voice_time = clock();
		}


		window.clear();
		window.draw(sprite_back);
		if (game_button == 1)
		{
			window.draw(text1);
			window.draw(sprite_play);
		}
		else
			window.draw(sprite_pause);
		window.draw(sprite_restart);
		window.draw(sprite_catapult);
		level1->draw(window);
		if (flag || game_over)
			window.draw(text);
		window.draw(sprite_catapult1);
		window.display();
	}
}

