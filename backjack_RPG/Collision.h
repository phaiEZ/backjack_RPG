#pragma once
#include <SFML\Graphics.hpp>
class Collision{
public:
	Collision(RectangleShape& body);
	~Collison();




private:
	sf::RectangleShape& body;
};

