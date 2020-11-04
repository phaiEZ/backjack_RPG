#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class enemy {
private:
	
	int hp;
	int enemyposx;
	int enemyposy;
public:
	enemy(sf::Texture* texture, int mostertype, int hpmoster, int enemyposy, int enemyposx);
	void draw(sf::RenderWindow& window);
	void takedamage();
	int GetHp() { return hp; }
	sf::RectangleShape Enemy;

};