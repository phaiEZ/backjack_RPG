#pragma once
#include <SFML\Graphics.hpp>
class player
{
public:
	Player();
	~Player();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow window);
private:
	sf::RectangleShape body;
	int posplayerx, posplayery;
	bool pressed;
};

