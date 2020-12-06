#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
enemy::enemy(sf::Texture *texture,int mostertype, int hpmoster ,int enemyposx , int enemyposy){
	Enemy.setSize(sf::Vector2f(50.0f, 50.0f));
	Enemy.setOrigin(0.f, 0.f);
	float x_size = texture->getSize().x / 32.000000;
	float y_size = texture->getSize().y / 32.000000;
	int Ennumx;
	int Ennumy;
	Enemy.setTexture(texture);
	if (mostertype > 28) {
		Ennumx = mostertype - 28;
		Ennumy = 9;
	}
	else if (mostertype > 21) {
		Ennumx = mostertype - 21;
		Ennumy = 8;
	}
	else if (mostertype > 14) {
		Ennumx = mostertype -14;
		Ennumy = 7;
	}
	else if (mostertype > 7) {
		Ennumx = mostertype - 7;
		Ennumy = 6;
	}
	else {
		Ennumx = mostertype;
		Ennumy = 5;
	}
	Enemy.setTextureRect(sf::IntRect(x_size * (24 + Ennumx), y_size * (0 + Ennumy), x_size, y_size));

	Enemy.setPosition(enemyposx, enemyposy);
	this->hp = hpmoster;
	this->maxhp = hpmoster;
}

void enemy::draw(sf::RenderWindow& window)
{
	window.draw(Enemy);

}

void enemy::takedamage(int damage)
{
	this->hp = hp - damage;
}
