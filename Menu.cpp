#include "Menu.h"

void menu(sf::RenderWindow& window, sf::Event& event)
{
	sf::Texture background, button_new, button_exit;
	sf::Sprite sprite_back, sprite_new, sprite_exit;
	background.loadFromFile("menu.png");
	sprite_back.setTexture(background);
	sprite_back.setPosition(0, 0);

	button_new.loadFromFile("new_game.png");
	sprite_new.setTexture(button_new);
	sprite_new.setPosition(360, 230);

	button_exit.loadFromFile("exit.png");
	sprite_exit.setTexture(button_exit);
	sprite_exit.setPosition(360, 270);

	sf::Font font;
	font.loadFromFile("FORTE.TTF");
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Yellow);
	text.setString("Menu");
	text.setCharacterSize(80);
	text.setPosition(350, 100);

	bool menu_flag = true;
	int menu_num = 0;
	bool mousepress = false;
	while (menu_flag)
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (sf::IntRect(360, 230, button_new.getSize().x, button_new.getSize().y).contains(sf::Mouse::getPosition(window)))
				{
					menu_num = 1;
					mousepress = true;
				}
				if (sf::IntRect(360, 270, button_exit.getSize().x, button_exit.getSize().y).contains(sf::Mouse::getPosition(window)))
				{
					menu_num = 2;
					mousepress = true;
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (menu_num == 1)
				{
					menu_flag = false;
				}
				if (menu_num == 2)
				{
					window.close();
					menu_flag = false;
				}
				break;
			}
		}
		window.draw(sprite_back);
		window.draw(text);
		window.draw(sprite_new);
		window.draw(sprite_exit);
		window.display();

	}
}
