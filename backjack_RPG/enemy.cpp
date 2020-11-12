#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
enemy::enemy(sf::Texture *texture,int mostertype, int hpmoster ,int enemyposy , int enemyposx){
	Enemy.setSize(sf::Vector2f(50.0f, 50.0f));
	Enemy.setOrigin(0.f, 0.f);
	sf::Texture texta;
	texta = *texture;
	sf::Vector2u textureSize = texta.getSize();
	float x_size = textureSize.x / 32.000000;
	float y_size = textureSize.y / 32.000000;
	Enemy.setTexture(&texta);
	if (mostertype == 1) {
		Enemy.setTextureRect(sf::IntRect(x_size * 29, y_size * 8, x_size, y_size));
	}
	else if (mostertype == 2) {
		Enemy.setTextureRect(sf::IntRect(x_size * 29, y_size * 6, x_size, y_size));
	}
	else if (mostertype == 3) {
		Enemy.setTextureRect(sf::IntRect(x_size * 29, y_size * 5, x_size, y_size));
	}
	
	Enemy.setPosition(enemyposx, enemyposy);
	this->hp = hpmoster;
	this->maxhp = hpmoster;
}

void enemy::draw(sf::RenderWindow& window)
{
	window.draw(Enemy);

}

void enemy::takedamage()
{
	this->hp = hp - 1;
}
