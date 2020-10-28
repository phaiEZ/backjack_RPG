#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<time.h>
#include <vector>
#include"card.h"
using namespace std;

int enemy_card;
int hero_card;
int Card[52];
int enemy_score = 0;
int hero_score = 0;
int a, i, x, j, k, c = 0;
char yes_no;
bool same;
int ispim[100];
std::vector <int> deck;

int pick_card() {
	srand(time(NULL));
	a = rand();
	a = (a % 52) + 1;
	same = true;
	while (same == true) {
		same = false;
		for (j = 0; j < 51; j++) {
			if (a == Card[j]) {
				same = true;
				a = rand();
				a = (a % 52) + 1;
			}
		}
	}
	Card[c] = a;
	c = c + 1;
	return (a);
}

int clear_card() {

	for (j = 0; j < 51; j++) {
		Card[j] = NULL;
		return 0;
	}
}

int winer(int a, int b) {
	if (a == b) {
		printf("draw  ;-; \n");
		return 0;
	}
	if (a > b) {
		printf("hero is winner  ^^ \n");
		return 0;
	}
	if (a < b) {
		printf("hero is lose  TT \n");
		return 0;
	}
}

int too_more(int a) {
	if (a > 21) {
		return(1);
	}
	else {
		return(0);
	}
}


int card_score(int a) {
	if (a <= 13) {
		if (a >= 10) {
			return(10);
		}
		else {
			return(a);
		}
	}
	else if (a <= 26) {
		a = a - 13;
		if (a >= 10) {
			return(10);
		}
		else {
			return(a);
		}
	}
	else if (a <= 39) {
		a = a - 26;
		if (a >= 10) {
			return(10);
		}
		else {
			return(a);
		}
	}
	else if (a <= 52) {
		a = a - 39;
		if (a >= 10) {
			return(10);
		}
		else {
			return(a);
		}
	}
}

char card_house(int a) {
	if (a <= 13) {
		return('s');
	}
	else if (a <= 26) {
		return('h');
	}
	else if (a <= 39) {
		return('c');
	}
	else if (a <= 52) {
		return('d');
	}
}

char card_type(int a) {
	if (a == 11 || a == 24 || a == 37 || a == 50) {
		return('J');
	}
	else if (a == 12 || a == 25 || a == 38 || a == 51) {
		return('Q');
	}
	else if (a == 13 || a == 26 || a == 39 || a == 52) {
		return('K');
	}
	else {
		return(' ');
	}
}



int main() {
	sf::RenderWindow window(sf::VideoMode(500, 500), "test", sf::Style::Close | sf::Style::Resize );
	//std::vector<card> deck;
	//card tc(&dkj);
	//tc.info.point
	//deck.push_back(tc);
	//for (card& Card : deck) Card.draw(window);
	sf::Texture Texture;
	Texture.loadFromFile("new2.png");
	sf::Vector2u textureSize = Texture.getSize();
	float x_size = textureSize.x / 32.000000;
	float y_size = textureSize.y / 32.000000;
	bool fight = false;
	bool enemydie = false;
	// card
	std::vector<card> deck;
	//card tc(&dkj);
	// wallx
	std::vector<sf::RectangleShape> wallx;
	sf::RectangleShape wall(sf::Vector2f(50.0f, 50.0f));
	for (int i = 1; i <= 20; i++)
	{
		float x = i*50;
		if (i <= 10) {
			wall.setPosition(x, 0.0f);
			wall.setTexture(&Texture);
			wall.setTextureRect(sf::IntRect(x_size * 23.00000, y_size * 3.00000, x_size, y_size));
			wall.setRotation(0.f);
			wall.rotate(90.f);
			wallx.push_back(wall);
		}
		else {
			x -= 500;
			wall.setPosition(x, 450.f);
			wall.setTexture(&Texture);
			wall.setTextureRect(sf::IntRect(x_size * 23.00000, y_size * 3.00000, x_size, y_size));
			wall.setRotation(0.f);
			wall.rotate(90.f);
			wallx.push_back(wall);
		}
	}
	// wally
	std::vector<sf::RectangleShape> wally;
	//sf::RectangleShape wall(sf::Vector2f(50.0f, 50.0f));
	for (int i = 1; i <= 16; i++){
		float x = i * 50;
		if (i <= 8) {
			wall.setPosition(0.0f, x);
			wall.setTexture(&Texture);
			wall.setTextureRect(sf::IntRect(x_size * 23.00000, y_size * 3.00000, x_size, y_size));
			wall.setRotation(0.f);
			wally.push_back(wall);
		}
		else {
			x -=  400;
			wall.setPosition(450.0f, x);
			wall.setTexture(&Texture);
			wall.setTextureRect(sf::IntRect(x_size * 23.00000, y_size * 3.00000, x_size, y_size));
			wall.setRotation(0.f);
			wally.push_back(wall);
		}
	}
	//player
	sf::RectangleShape player(sf::Vector2f(50.0f, 50.0f));
	player.setOrigin(0.f, 0.f);
	player.setPosition(50.0f, 50.0f);
	player.setTexture(&Texture);
	player.setTextureRect(sf::IntRect(x_size * 25, y_size * 0, x_size, y_size));
	// position
	int player_posx = 1;
	int player_posy = 1;


	//enemy
	sf::RectangleShape enemy(sf::Vector2f(50.0f, 50.0f));
	enemy.setOrigin(0.f, 0.f);
	enemy.setPosition(250.0f, 300.0f);
	enemy.setTexture(&Texture);
	enemy.setTextureRect(sf::IntRect(x_size * 29, y_size * 8, x_size, y_size));
	// position
	int enemy_posx = 5;
	int enemy_posy = 6;

	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				std::cout << "width" << evnt.size.width << "height" << evnt.size.height << std::endl;
				break;
			case sf::Event::TextEntered:
				if (evnt.text.unicode < 128) {
					printf("%c", evnt.text.unicode);
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)  && player_posx!=1 ) {
			player.move(-50.f,0.f);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			}
			player_posx -= 1;
			printf("position x = %d position y = %d",player_posx,player_posy);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && player_posx != 8 ) {
			player.move(50.f, 0.0f);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			}
			player_posx += 1;
			printf("position x = %d position y = %d", player_posx, player_posy);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && player_posy != 1) {
			player.move(0.0f, -50.f);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			}
			player_posy -= 1;
			printf("position x = %d position y = %d", player_posx, player_posy);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && player_posy != 8) {
			player.move(0.0f, 50.f);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			}
			player_posy += 1;
			printf("position x = %d position y = %d", player_posx, player_posy);
		}
		if (player.getGlobalBounds().intersects(enemy.getGlobalBounds()) && enemydie == false) {
			fight = true;
		}
		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x, (float)mousePos.y);
		}
		*/
		window.clear();
		for (int i = 0; i < wallx.size(); i++){
			window.draw(wallx[i]);
		}
		for (int i = 0; i < wally.size(); i++){
			window.draw(wally[i]);
		}
		if (enemydie != true) {
			window.draw(enemy);
		}
		if (fight == true) {
			while (fight == true) {
				if (ispim[2] == 0) {
					hero_card = pick_card();
					enemy_card = pick_card();
					hero_score += card_score(hero_card);
					enemy_score += card_score(enemy_card);
					ispim[2] = 1;
				}
				if (ispim[0] == 0) {
					printf_s("\nhero is %d %c ", card_score(hero_card), card_house(hero_card));
					ispim[0] = 1;
				}
				//printf_s("enemy is %d %c", card_score(enemy_card), card_house(enemy_card));
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
					hero_card = pick_card();
					enemy_card = pick_card();
					hero_score += card_score(hero_card);
					enemy_score += card_score(hero_card);
					printf_s("\nhero draw is %d %c", card_score(hero_card), card_house(hero_card));
					printf_s("\nhero is  score is %d", hero_score);
					while(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)){
					}
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
					break;
				}
			}
			printf_s("\nhero is %d",hero_score);
			printf_s("\nenemy is %d",enemy_score);
			printf("\n fight done");
			enemydie = true;
			fight = false;
		}
		window.draw(player);
		window.display();
	}
	return 0;
}