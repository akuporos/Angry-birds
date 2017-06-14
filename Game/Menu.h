#pragma once

#include <SFML/Graphics.hpp>

class Menu
{
	sf::Texture background, button_new, button_exit;
	sf::Sprite sprite_back, sprite_new, sprite_exit;
	sf::Font font;
	sf::Text text;
	bool menu_flag = true;
	int menu_num = 0;
	bool mousepress = false;
	bool flag_first_menu = false;
public:
	Menu(bool& flag_first_menu);
	void event_handler(sf::RenderWindow & window, sf::Event& event);
	void draw(sf::RenderWindow & window);

	~Menu();
	
};