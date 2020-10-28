#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class card {
private:
	sf::RectangleShape body;
public:
	struct cardinfo {
		int point;
		char sym;
	}info;
	card(sf::Texture& texure);
	void draw(sf::RenderWindow &window);
	
};



