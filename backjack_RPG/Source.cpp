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
bool fight = false;
bool enemydie = false;
int walk;
std::vector <int> Deck;
std::vector <int> hand_hero;
std::vector <int> hand_enemy;

int level_map =0;

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
int Shuffle() {
	for (int kk = 0; kk < 52; kk++) {
		Deck.push_back(pick_card());
	}
	return 0;
}

int clear_card() {
	for (j = 0; j < 51; j++) {
		Card[j] = NULL;
	}
	while (not Deck.empty()) Deck.pop_back();
	return 0;
}

int winer(int a, int b) {
	if (a == b) {
		printf("draw  ;-; \n");
		return 0;
	}
	if (a > b) {
		printf("hero is winner  ^^ \n");
		enemydie = true;
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
	sf::RenderWindow window(sf::VideoMode(500, 500), "test", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(60);
	//card tc(&dkj);
	//tc.info.point
	//deck.push_back(tc);
	//for (card& Card : deck) Card.draw(window);
	sf::Texture Texture;
	Texture.loadFromFile("new2.png");
	sf::Vector2u textureSize = Texture.getSize();
	float x_size = textureSize.x / 32.000000;
	float y_size = textureSize.y / 32.000000;
	// card
	//card tc(&dkj);

	int wall_location[10][100] =
		//1
	{ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		//2
	{   1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 0, 0, 1, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 0, 1,
		1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	std::vector<sf::RectangleShape> Wall;
	sf::RectangleShape wall(sf::Vector2f(50.0f, 50.0f));
	


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
		int row = 0;
		int row_count = 0;
		for (int i = 0; i <= 99; i++) {
			if (row_count == 10) {
				//printf("*");
				row_count = 0;
				row += 1;
			}
			if (wall_location[level_map][i] == 1) {
				wall.setPosition(50 * row_count, row * 50);
				wall.setTexture(&Texture);
				wall.setTextureRect(sf::IntRect(x_size * 23.00000, y_size * 3.00000, x_size, y_size));
				wall.setRotation(0.f);
				Wall.push_back(wall);
			}
			row_count += 1;
		}


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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			player.move(-50.f, 0.f);
			walk = 1;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			}
			player_posx -= 1;
			//printf("position x = %d position y = %d",player_posx,player_posy);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player.move(50.f, 0.0f);
			walk = 2;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			}
			player_posx += 1;
			//printf("position x = %d position y = %d", player_posx, player_posy);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			player.move(0.0f, -50.f);
			walk = 3;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			}
			player_posy -= 1;
			//printf("position x = %d position y = %d", player_posx, player_posy);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			player.move(0.0f, 50.f);
			walk = 4;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			}
			player_posy += 1;
			//printf("position x = %d position y = %d", player_posx, player_posy);
		}
		if (player.getGlobalBounds().intersects(enemy.getGlobalBounds()) && enemydie == false) {
			fight = true;
		}
		for (int i = 0; i < Wall.size(); i++) {
			if (player.getGlobalBounds().intersects(Wall[i].getGlobalBounds())) {
				if (walk == 1) {
					player.move(50.f, 0.f);
					player_posx += 1;
				}
				else if (walk == 2) {
					player.move(-50.f, 0.0f);
					player_posx -= 1;
				}
				else if (walk == 3) {
					player.move(0.0f, 50.f);
					player_posy += 1;
				}
				else if (walk == 4) {
					player.move(0.0f, -50.f);
					player_posy -= 1;
				}
			}
		}

		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x, (float)mousePos.y);
		}
		*/

		window.clear();


		for (int i = 0; i < Wall.size(); i++) {
			window.draw(Wall[i]);
		}


		if (enemydie != true) {
			window.draw(enemy);
		}
		if (fight == true) {
			Shuffle();
			while (fight == true) {
				for (int i = 0; i < Deck.size(); i++) {
					printf("\n%d ", Deck[i]);
				}
				hand_hero.push_back(Deck.back());
				hero_score += card_score(Deck.back());
				Deck.pop_back();
				hand_enemy.push_back(Deck.back());
				enemy_score += card_score(Deck.back());
				Deck.pop_back();
				hand_hero.push_back(Deck.back());
				hero_score += card_score(Deck.back());
				Deck.pop_back();
				hand_enemy.push_back(Deck.back());
				enemy_score += card_score(Deck.back());
				Deck.pop_back();
				printf("\nhand hero\n");
				for (int i = 0; i < hand_hero.size(); i++) {
					printf(" %d", hand_hero[i]);
				}
				printf("hero score");
				printf("%d", hero_score);
				while (1) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
						hand_hero.push_back(Deck.back());
						hero_score += card_score(Deck.back());
						Deck.pop_back();
						if (too_more(hero_score) == 1) {
							printf_s("\nhero is %d", hero_score);
							printf_s("\nenemy is %d\n", enemy_score);
							printf("hero is lose  TT \n");
							if (walk == 1) {
								player.move(50.f, 0.f);
								player_posx += 1;
							}
							else if (walk == 2) {
								player.move(-50.f, 0.0f);
								player_posx -= 1;
							}
							else if (walk == 3) {
								player.move(0.0f, 50.f);
								player_posy += 1;
							}
							else if (walk == 4) {
								player.move(0.0f, -50.f);
								player_posy -= 1;
							}
							break;
						}
						hand_enemy.push_back(Deck.back());
						enemy_score += card_score(Deck.back());
						Deck.pop_back();
						if (too_more(enemy_score) == 1) {
							printf_s("\nhero is %d", hero_score);
							printf_s("\nenemy is %d\n", enemy_score);
							printf("hero is winner  ^^ \n");
							enemydie = true;
							break;
						}
						printf("\nhand hero\n");
						for (int i = 0; i < hand_hero.size(); i++) {
							printf(" %d", hand_hero[i]);
						}
						printf("hero score");
						printf("%d", hero_score);
						while (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
						fight = false;
						printf_s("\nhero is %d", hero_score);
						printf_s("\nenemy is %d\n", enemy_score);
						winer(hero_score, enemy_score);
						break;
						while (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {}
					}
				}
				clear_card();
				enemy_score = 0;
				hero_score = 0;
				while (not hand_hero.empty()) hand_hero.pop_back();
				while (not hand_enemy.empty()) hand_enemy.pop_back();
				fight = false;
				level_map++;
				player.setPosition(50.0f, 50.0f);
			}
		}


		window.draw(player);
		window.display();
	}
	return 0;
}