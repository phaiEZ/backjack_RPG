#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<time.h>
#include <vector>
#include"card.h"
#include "enemy.h"
using namespace std;

#define GRID_WIDTH 11
#define GRID_HEIGHT 11
#define NORTH 1
#define EAST 0
#define SOUTH 2
#define WEST 3

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
int enemynum;
int level_map = 0;
std::vector <enemy> Enemyvec;
std::vector < int > wall_location;
char grid[GRID_WIDTH * GRID_HEIGHT];

void ResetGrid()
{

	for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i)
	{
		grid[i] = '1';
	}
}

int XYToIndex(int x, int y)
{

	return y * GRID_WIDTH + x;
}

int IsInBounds(int x, int y)
{

	if (x < 0 || x >= GRID_WIDTH)
		return false;
	if (y < 0 || y >= GRID_HEIGHT)
		return false;
	return true;
}

void Visit(int x, int y) {
	grid[XYToIndex(x, y)] = '0';
	int dirs[4];
	dirs[0] = NORTH;
	dirs[1] = EAST;
	dirs[2] = SOUTH;
	dirs[3] = WEST;
	for (int i = 0; i < 4; ++i)
	{
		int r = rand() & 3;
		int temp = dirs[r];
		dirs[r] = dirs[i];
		dirs[i] = temp;
	}
	for (int i = 0; i < 4; ++i)
	{
		int dx = 0, dy = 0;
		switch (dirs[i])
		{
		case NORTH:
			dy = -1;
			break;
		case SOUTH:
			dy = 1;
			break;
		case EAST:
			dx = 1;
			break;
		case WEST:
			dx = -1;
			break;
		}
		int x2 = x + (dx << 1);
		int y2 = y + (dy << 1);
		if (IsInBounds(x2, y2))
		{
			if (grid[XYToIndex(x2, y2)] == '1') {
				grid[XYToIndex(x2 - dx, y2 - dy)] = '0';
				Visit(x2, y2);
			}
		}
	}
}

void PrintGrid()
{
	for (int y = 0; y < GRID_HEIGHT; ++y)
	{
		for (int x = 0; x < GRID_WIDTH; ++x)
		{

			//cout << grid[XYToIndex(x, y)];
			wall_location.push_back(grid[XYToIndex(x, y)]);
			//pushbackwall
		}
		//cout << endl;
	}
}


int randommap() {
	while (not wall_location.empty()) wall_location.pop_back();
	srand(time(NULL));
	ResetGrid();
	Visit(1,1);
	PrintGrid();
	return 0;
}
////////////////////////////////////////////////////////////

int pick_card() {
	srand(time(NULL));
	a = rand();
	a = (a % 52) + 1;
	same = true;
	while (same == true) {
		same = false;
		for (int jk = 0; jk <= 51; jk++) {
			if (a == Card[jk]) {
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
	c = 0;
	for (int kk = 0; kk <= 51; kk++) {
		Deck.push_back(pick_card());
	}
	return 0;
}

int clear_card() {
	for (int jj = 0; jj <= 51; jj++) {
		Card[jj] = -1;
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
		Enemyvec[enemynum].takedamage();
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
}



int main() {
	randommap();
	sf::RenderWindow window(sf::VideoMode(550, 550), "Black_jack_rpg0.1", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(30);
	sf::Texture Texture;
	Texture.loadFromFile("new2.png");
	sf::Vector2u textureSize = Texture.getSize();
	float x_size = textureSize.x / 32.000000;
	float y_size = textureSize.y / 32.000000;

	

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
	

	//card
	std::vector<sf::RectangleShape> Card;
	for (float i = 0; i <= 52; i++) {
		if (i <= 13 && i > 0) {
			sf::RectangleShape card(sf::Vector2f(30.0f, 30.0f));
			card.setTexture(&Texture);
			card.setTextureRect(sf::IntRect(x_size * (18.00000 + i), y_size * 16.00000, x_size, y_size));
			Card.push_back(card);
		}
		else if (i > 13 && i <= 26) {
			sf::RectangleShape card(sf::Vector2f(30.0f, 30.0f));
			card.setTexture(&Texture);
			card.setTextureRect(sf::IntRect(x_size * (18.00000 + i - 13), y_size * 17.00000, x_size, y_size));
			Card.push_back(card);
		}
		else if (i > 26 && i <= 39) {
			sf::RectangleShape card(sf::Vector2f(30.0f, 30.0f));
			card.setTexture(&Texture);
			card.setTextureRect(sf::IntRect(x_size * (18.00000 + i - 26), y_size * 18.00000, x_size, y_size));
			Card.push_back(card);
		}
		else if (i > 39) {
			sf::RectangleShape card(sf::Vector2f(30.0f, 30.0f));
			card.setTexture(&Texture);
			card.setTextureRect(sf::IntRect(x_size * (18.00000 + i - 39), y_size * 19.00000, x_size, y_size));
			Card.push_back(card);
		}
	}

	enemy x(&Texture, 2, 2, 100, 100);
	x.Enemy.setTexture(&Texture);
	Enemyvec.push_back(x);

	enemy a(&Texture, 1, 2, 300, 100);
	a.Enemy.setTexture(&Texture);
	Enemyvec.push_back(a);

	enemy b(&Texture, 3, 2, 400, 100);
	b.Enemy.setTexture(&Texture);
	Enemyvec.push_back(b);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		int row = 0;
		int row_count = 0;
		while (not Wall.empty()) Wall.pop_back();
		for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
			if (row_count == GRID_WIDTH) {
				//printf("*");
				row_count = 0;
				row += 1;
			}
			if (wall_location[i] == '1') {
				wall.setPosition(50 * row_count, row * 50);
				wall.setTexture(&Texture);
				wall.setTextureRect(sf::IntRect(x_size * 23.00000, y_size * 3.00000, x_size, y_size));
				Wall.push_back(wall);
			}
			row_count += 1;
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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {

			randommap();
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			}
		}
		
		for (int i = 0; i < Enemyvec.size(); i++) {
			if (player.getGlobalBounds().intersects(Enemyvec[i].Enemy.getGlobalBounds()) && (Enemyvec[i].GetHp()) > 0) {
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
				fight = true;
				enemynum = i;
			}
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
		window.clear();


		for (int i = 0; i < Wall.size(); i++) {
			window.draw(Wall[i]);
		}
		for (int i = 0; i < Enemyvec.size(); i++) {
			if ((Enemyvec[i].GetHp()) > 0) {
				Enemyvec[i].draw(window);
			}
		}
		if (fight == true) {
			while (fight == true) {
				clear_card();
				Shuffle();
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
							break;
						}
						hand_enemy.push_back(Deck.back());
						enemy_score += card_score(Deck.back());
						Deck.pop_back();
						if (too_more(enemy_score) == 1) {
							printf_s("\nhero is %d", hero_score);
							printf_s("\nenemy is %d\n", enemy_score);
							printf("hero is winner  ^^ \n");
							Enemyvec[enemynum].takedamage();
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
						while (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {}
						break;
					}
				}
				clear_card();
				enemy_score = 0;
				hero_score = 0;
				while (not hand_hero.empty()) hand_hero.pop_back();
				while (not hand_enemy.empty()) hand_enemy.pop_back();
				fight = false;
				break;
			}
		}
		window.draw(player);
		/*
		int h = 0;
		int c = 0;
		for (int i = 0; i < 52; i++)
		{
			Card[i].setPosition(50+c,50);
			window.draw(Card[i]);
			c += 15;
			
		}
		*/
		//window.draw(playercard);
		window.display();
	}
	return 0;
	
}