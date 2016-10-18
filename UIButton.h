#ifndef BUTTON
#define BUTTON

#include <SFML/Graphics.hpp>

class UIButton
{
public:
	UIButton();
	void press(sf::Vector2i & mouse_coords, sf::Event & event);
	void released(sf::Vector2i & mouse_coords, sf::Event & event);
};
#endif

