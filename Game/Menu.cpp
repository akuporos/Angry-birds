#include "Menu.h"

Menu::Menu(bool& flag_menu)
{
	flag_first_menu = flag_menu;
	background.loadFromFile("picture/menu.png");
	sprite_back.setTexture(background);
	sprite_back.setPosition(0, 0);
	
	if (!flag_first_menu)
	{
		button_new.loadFromFile("picture/new_game.png");
		sprite_new.setTexture(button_new);
		sprite_new.setPosition(360, 230);
	}
	else
	{
		button_new.loadFromFile("picture/continue.png");
		sprite_new.setTexture(button_new);
		sprite_new.setPosition(360, 230);
	}
	button_exit.loadFromFile("picture/exit.png");
	sprite_exit.setTexture(button_exit);
	sprite_exit.setPosition(360, 270);

	font.loadFromFile("FORTE.TTF");
	text.setFont(font);
	text.setFillColor(sf::Color::Yellow);
	text.setString("Menu");
	text.setCharacterSize(80);
	text.setPosition(350, 100);

}

void Menu::event_handler(sf::RenderWindow & window, sf::Event & event)
{
	bool flag_ret = false;
	while (menu_flag)
	{
		if (flag_ret)
			break;
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
				case sf::Keyboard::Escape:
					if (flag_first_menu)
					{
						flag_ret = true;
					}
					break;
				}
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
void Menu::draw(sf::RenderWindow & window)
{

}

Menu::~Menu()
{

}