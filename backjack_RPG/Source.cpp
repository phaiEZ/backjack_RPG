#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
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
#include <stdio.h>
using namespace std;

#define GRID_WIDTH 11
#define GRID_HEIGHT 11
#define NORTH 1
#define EAST 0
#define SOUTH 2
#define WEST 3

float shiftx = 200;
float shifty = 100;

bool isdraw = false;

bool newgame = true;
int enemy_card;
int hero_card;
int Card[52];
int enemy_score = 0;
int hero_score = 0;
int a;
int i;
int x;
int j;
int k;
int c = 0;
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
std::vector < int > wall_location;
char grid[GRID_WIDTH * GRID_HEIGHT];
int level = 0;
sf::Clock cl;
float Time;
int herodamage;
int herohp;
int sheildnum;
int coin;
int levelten = 0;
int playernumx = 0;
int playernumy = 0;
int VOL = 50;
bool ispause = false;
std::vector <enemy> Enemyvec;


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
	while (not Enemyvec.empty()) Enemyvec.pop_back();
	srand(time(NULL));
	ResetGrid();
	Visit(1, 1);
	PrintGrid();
	level++;
	return 0;
}
////////////////////////////////////////////////////////////

int randoM(int min, int max) {
	a = rand();
	a = (a % max) + 1;
	while (1) {
		if (a < min) {
			a = rand();
			a = (a % max) + 1;
		}
		else {
			break;
		}
	}
	return(a);
}


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

static const float VIEW_HEIGHT = 1300.0f; //900


void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);

	view.setSize(VIEW_HEIGHT * aspectRatio * 1, VIEW_HEIGHT * 3);
}

void herogetdamage() {
	if(sheildnum >= 1) {
			sheildnum = sheildnum - 1;
	}
	else if (herohp > 0){
		herohp = herohp - 1;
	}
}

int winer(int a, int b) {
	if (a == b) {
		printf("draw  ;-; \n");
		return 0;
	}
	if (a > b) {
		printf("hero is winner  ^^ \n");
		Enemyvec[enemynum].takedamage(herodamage);
		return 0;
	}
	if (a < b) {
		printf("hero is lose  TT \n");
		herogetdamage();
		return 0;
	}
}
int main() {
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(550 + shiftx, 550 + shifty), "Black_jack_rpg0.1", sf::Style::Close | sf::Style::Fullscreen); 
	window.setFramerateLimit(200);
	sf::Texture Texture;
	Texture.loadFromFile("new2.png");
	sf::Vector2u textureSize = Texture.getSize();
	float x_size = textureSize.x / 32.000000;
	float y_size = textureSize.y / 32.000000;

	sf::View view(sf::Vector2f(+500.0f, +350.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT * 0.6));
	std::vector<sf::RectangleShape> Wall;
	sf::RectangleShape wall(sf::Vector2f(50.0f, 50.0f));

	//player
	sf::RectangleShape player(sf::Vector2f(50.0f, 50.0f));
	player.setOrigin(0.f, 0.f);
	player.setPosition(50.0f + shiftx, 50.0f + shifty);
	player.setTexture(&Texture);
	//player.setFillColor(sf::Color::Red);
	player.setTextureRect(sf::IntRect(x_size * 25, y_size * 0, x_size, y_size));


	// door
	sf::RectangleShape Door(sf::Vector2f(50.0f, 50.0f));
	Door.setOrigin(0.f, 0.f);
	Door.setPosition(450.0f + shiftx, 50.0f + shifty);
	Door.setTexture(&Texture);
	Door.setTextureRect(sf::IntRect(x_size * 3, y_size * 6, x_size, y_size));


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

	std::vector<sf::RectangleShape> shielditem;
	std::vector<sf::RectangleShape> damageitem;
	std::vector<sf::RectangleShape> Coinitem;
	std::vector<sf::RectangleShape> healposion;
	sf::RectangleShape item(sf::Vector2f(50.0f, 50.0f));
	// healposion
	
	sf::Texture papertex;
	papertex.loadFromFile("paper.png");
	sf::RectangleShape paper(sf::Vector2f(500.0f, 500.0f));
	paper.setOrigin(0.f, 0.f);
	paper.setPosition(-103.0f, 20.0f);
	paper.setTexture(&papertex);

	//std::vector <enemy> Enemyvec;
	

	sf::Texture menutex;
	menutex.loadFromFile("menu.png");
	sf::RectangleShape menu(sf::Vector2f(1200.0f, 675.0f));
	menu.setOrigin(0.f, 0.f);
	menu.setPosition(-103.0f, 20.0f);
	menu.setTexture(&menutex);
	//player.setFillColor(sf::Color::Red);

	sf::Texture menutex2;
	menutex2.loadFromFile("menu2.png");
	sf::RectangleShape menu2(sf::Vector2f(1200.0f, 675.0f));
	menu2.setOrigin(0.f, 0.f);
	menu2.setPosition(-103.0f, 20.0f);
	menu2.setTexture(&menutex2);

	sf::Texture menutex3;
	menutex3.loadFromFile("menu3.png");
	sf::RectangleShape menu3(sf::Vector2f(1200.0f, 675.0f));
	menu3.setOrigin(0.f, 0.f);
	menu3.setPosition(-103.0f, 20.0f);
	menu3.setTexture(&menutex3);

	sf::Texture menutex4;
	menutex4.loadFromFile("menu4.png");
	sf::RectangleShape menu4(sf::Vector2f(1200.0f, 675.0f));
	menu4.setOrigin(0.f, 0.f);
	menu4.setPosition(-103.0f, 20.0f);
	menu4.setTexture(&menutex4);

	sf::Texture menutex5;
	menutex5.loadFromFile("menu5.png");
	sf::RectangleShape menu5(sf::Vector2f(1200.0f, 675.0f));
	menu5.setOrigin(0.f, 0.f);
	menu5.setPosition(-103.0f, 20.0f);
	menu5.setTexture(&menutex5);

	sf::Texture menutex6;
	menutex6.loadFromFile("inputnamemenu.png");
	sf::RectangleShape menu6(sf::Vector2f(1200.0f, 675.0f));
	menu6.setOrigin(0.f, 0.f);
	menu6.setPosition(-103.0f, 20.0f);
	menu6.setTexture(&menutex6);


	//sf::Texture b;
	//menutex.loadFromFile("menu.png");
	sf::RectangleShape buttol(sf::Vector2f(185.0f, 55.0f));
	buttol.setOrigin(50.f, 50.f);
	buttol.setPosition(945.0f, 300.0f);
	//menu.setTexture(&menutex);
	sf::RectangleShape buttolunder(sf::Vector2f(180.0f, 5.0f));
	buttolunder.setOrigin(50.f, 50.f);
	buttolunder.setPosition(947.0f, 360.0f);

	sf::RectangleShape buttol2(sf::Vector2f(140.0f, 30.0f));
	buttol2.setOrigin(50.f, 50.f);
	buttol2.setPosition(994.0f, 415.0f);
	//menu.setTexture(&menutex);
	sf::RectangleShape buttolunder2(sf::Vector2f(140.0f, 5.0f));
	buttolunder2.setOrigin(50.f, 50.f);
	buttolunder2.setPosition(996.0f, 445.0f);

	sf::RectangleShape buttol3(sf::Vector2f(294.0f, 30.0f));
	buttol3.setOrigin(50.f, 50.f);
	buttol3.setPosition(842.0f, 452.0f);
	//menu.setTexture(&menutex);
	sf::RectangleShape buttolunder3(sf::Vector2f(294.0f, 5.0f));
	buttolunder3.setOrigin(50.f, 50.f);
	buttolunder3.setPosition(842.0f, 482.0f);

	sf::RectangleShape buttol4(sf::Vector2f(245.0f, 30.0f));
	buttol4.setOrigin(50.f, 50.f);
	buttol4.setPosition(895.0f, 492.0f);
	//menu.setTexture(&menutex);
	sf::RectangleShape buttolunder4(sf::Vector2f(245.0f, 5.0f));
	buttolunder4.setOrigin(50.f, 50.f);
	buttolunder4.setPosition(895.0f, 522.0f);


	
	sf::RectangleShape buttol5(sf::Vector2f(105.0f, 30.0f));
	buttol5.setOrigin(50.f, 50.f);
	buttol5.setPosition(1035.0f, 529.0f);

	sf::RectangleShape buttolunder5(sf::Vector2f(105.0f, 5.0f));
	buttolunder5.setOrigin(50.f, 50.f);
	buttolunder5.setPosition(1035.0f, 559.0f);


	sf::RectangleShape corsor(sf::Vector2f(25.f, 25.f));
	corsor.setOrigin(12.5f, 12.5f);
	corsor.setTexture(&Texture);
	corsor.setTextureRect(sf::IntRect(x_size * 22.00000000 , y_size * 22.000000, x_size, y_size));

	sf::Texture arrowrighttex;
	arrowrighttex.loadFromFile("arrowright.png");
	sf::RectangleShape arrowright(sf::Vector2f(105.0f, 105.0f));
	arrowright.setOrigin(0.f, 0.f);
	arrowright.setTexture(&arrowrighttex);

	sf::Texture arrowlefttex;
	arrowlefttex.loadFromFile("arrowleft.png");
	sf::RectangleShape arrowleft(sf::Vector2f(105.0f, 105.0f));
	arrowleft.setOrigin(0.f, 0.f);
	arrowleft.setTexture(&arrowlefttex);

	sf::RectangleShape playerselect(sf::Vector2f(150.0f, 150.0f));
	playerselect.setOrigin(0.f, 0.f);
	playerselect.setTexture(&Texture);;
	playerselect.setTextureRect(sf::IntRect(x_size * 25, y_size * 0, x_size, y_size));

	sf::RectangleShape volume(sf::Vector2f(50.0f, 50.0f));
	volume.setOrigin(0.f, 0.f);
	volume.setTexture(&Texture);;
	volume.setPosition(500.0f,0.0f);
	volume.setTextureRect(sf::IntRect(x_size * 25, y_size * 22, x_size, y_size));


	sf::Texture pausetex;
	pausetex.loadFromFile("pause.png");
	sf::RectangleShape pause(sf::Vector2f(500.0f, 500.0f));
	pause.setTexture(&pausetex);;
	pause.setPosition(226.0f, 110.0f);

	sf::Texture pause_menu_tex;
	pause_menu_tex.loadFromFile("pause_menu_icon.png");
	sf::RectangleShape pause_menu(sf::Vector2f(80.0f, 80.0f));
	pause_menu.setTexture(&pause_menu_tex);;
	pause_menu.setPosition(280.0f, 420.0f);

	sf::Texture pause_volumemax_tex;
	pause_volumemax_tex.loadFromFile("pause_volume_icon.png");

	sf::Texture pause_volumelow_tex;
	pause_volumelow_tex.loadFromFile("pause_volumeoff_icon.png");

	sf::RectangleShape pause_volume(sf::Vector2f(80.0f, 80.0f));
	pause_volume.setTexture(&pause_volumemax_tex);;
	pause_volume.setPosition(380.0f, 420.0f);

	sf::Texture pause_suicide_tex;
	pause_suicide_tex.loadFromFile("pause_suicide_icon.png");
	sf::RectangleShape pause_suicide(sf::Vector2f(80.0f, 80.0f));
	pause_suicide.setTexture(&pause_suicide_tex);;
	pause_suicide.setPosition(480.0f, 420.0f);

	sf::Texture pause_play_tex;
	pause_play_tex.loadFromFile("pause_play_icon.png");
	sf::RectangleShape pause_play(sf::Vector2f(80.0f, 80.0f));
	pause_play.setTexture(&pause_play_tex);;
	pause_play.setPosition(580.0f, 420.0f);


	sf::RectangleShape player_dead(sf::Vector2f(80.0f, 80.0f));
	player_dead.setTexture(&Texture);;
	player_dead.setPosition(0.0f, 0.0f);


	int screen = 0;
	
	sf::Music Song;
	Song.openFromFile("snd/The_Bards_Tale.wav");
	Song.setVolume(VOL);
	Song.getLoop();
	Song.play();

	sf::SoundBuffer swoosh;
	swoosh.loadFromFile("snd/swooshClose.wav");
	sf::Sound Swoosh;
	Swoosh.setBuffer(swoosh);

	sf::SoundBuffer coins;
	coins.loadFromFile("snd/coin.wav");
	sf::Sound Coin;
	Coin.setBuffer(coins);

	sf::SoundBuffer heal;
	heal.loadFromFile("snd/heal.wav");
	sf::Sound Heal;
	Heal.setBuffer(heal);

	sf::SoundBuffer shield;
	shield.loadFromFile("snd/shield.wav");
	sf::Sound Shield;
	Shield.setBuffer(shield);

	sf::SoundBuffer equip;
	equip.loadFromFile("snd/equip.wav");
	sf::Sound Equip;
	Equip.setBuffer(equip);

	sf::SoundBuffer attack;
	attack.loadFromFile("snd/attack.wav");
	sf::Sound Attack;
	Attack.setBuffer(attack);

	sf::SoundBuffer attacked;
	attacked.loadFromFile("snd/attacked.wav");
	sf::Sound Attacked;
	Attacked.setBuffer(attacked);

	sf::SoundBuffer step;
	step.loadFromFile("snd/step.wav");
	sf::Sound Step;
	Step.setBuffer(step);

	sf::SoundBuffer win;
	win.loadFromFile("snd/win.wav");
	sf::Sound Win;
	Win.setBuffer(win); 

	sf::SoundBuffer stairs;
	stairs.loadFromFile("snd/stairs.wav");
	sf::Sound Stairs;
	Stairs.setBuffer(stairs);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (window.isOpen()) {
		window.clear();
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				std::cout << "width" << evnt.size.width << "height" << evnt.size.height << std::endl;
				ResizeView(window, view);
				break;
			case sf::Event::TextEntered:
				if (evnt.text.unicode < 128) {
					//printf("%c", evnt.text.unicode);
				}
			}
		}
		window.setMouseCursorVisible(false);
		if (screen == 0) {
			window.clear();
			window.setView(view);
			window.draw(menu);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)|| sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				}
				screen = 1;
			}
			window.setView(view);
			window.display();
		}
		if (screen == 1) {
			window.clear();
			Song.setVolume(VOL);
			//window.setView(view);
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			corsor.setPosition((float)mousePos.x -300, (float)mousePos.y - 300);
			window.draw(menu2);
			//window.draw(buttol5);
			volume.setPosition(1050.0f, 0.0f);
			volume.setFillColor(sf::Color(255, 255, 255, 255));

			if (VOL == 0) {
				volume.setTextureRect(sf::IntRect(x_size * 21, y_size * 28, x_size, y_size));
		}
			else {
				volume.setTextureRect(sf::IntRect(x_size * 22, y_size * 28, x_size, y_size));
			}


		if (corsor.getGlobalBounds().intersects(volume.getGlobalBounds())) {
			volume.setFillColor(sf::Color(255, 255, 255, 128));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				}
				if (VOL == 0) {
					VOL = 50;
				}
				else {
					VOL = 0;
				}
			}
		}



			if (corsor.getGlobalBounds().intersects(buttol.getGlobalBounds())) {
				window.draw(buttolunder);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					Swoosh.play();
					newgame = true;
					playernumx = 0;
					playernumy = 0;
					screen = 7;
				}
			}
			else if (corsor.getGlobalBounds().intersects(buttol2.getGlobalBounds())) {
				//window.draw(buttolunder2);
				window.draw(buttolunder2);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					Swoosh.play();
					screen = 2;
				}
			}
			else if (corsor.getGlobalBounds().intersects(buttol3.getGlobalBounds())) {
				window.draw(buttolunder3);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					Swoosh.play();
					newgame = true;
					screen = 4;
				}
			}
			else if (corsor.getGlobalBounds().intersects(buttol4.getGlobalBounds())) {
				window.draw(buttolunder4);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					Swoosh.play();
					newgame = true;
					screen = 5;
				}
			}
			else if (corsor.getGlobalBounds().intersects(buttol5.getGlobalBounds())) {
				window.draw(buttolunder5);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					return 0;
				}
			}
			window.draw(volume);
			window.setView(view);
			window.draw(corsor);
			window.display();
		}

		if (screen == 7) {
			window.clear();
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			corsor.setPosition((float)mousePos.x - 300, (float)mousePos.y - 300);
			arrowright.setFillColor(sf::Color(255, 255, 255, 255));
			arrowleft.setFillColor(sf::Color(255, 255, 255, 255));
			if (playernumx >= 7) {
				playernumx = 0;
				playernumy++;
			}
			if (playernumx < 0) {
				playernumx = 6;
				playernumy--;
			}
			if (playernumy >= 10) {
				playernumy = 0;
			}
			if (playernumy < 0) {
				playernumy = 9;
			}
			playerselect.setTextureRect(sf::IntRect(x_size * (25 + playernumx), y_size * (0 + playernumy), x_size, y_size));

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				screen = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				player.setTextureRect(sf::IntRect(x_size* (25 + playernumx), y_size* (0 + playernumy), x_size, y_size));
				player_dead.setTextureRect(sf::IntRect(x_size* (25 + playernumx), y_size* (0 + playernumy), x_size, y_size));
				screen = 6;
			}
			else if (corsor.getGlobalBounds().intersects(arrowright.getGlobalBounds())) {
				arrowright.setFillColor(sf::Color(255,255,255,128));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					}
					playernumx++;
				}
			}
			else if (corsor.getGlobalBounds().intersects(arrowleft.getGlobalBounds())) {
				arrowleft.setFillColor(sf::Color(255, 255, 255, 128));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					}
					playernumx--;
				}
			}
			arrowright.setPosition(750.f, 260.f);
			arrowleft.setPosition(130.f, 260.f);
			playerselect.setPosition(415.f, 240.f);
			window.draw(menu6);
			window.draw(arrowleft);
			window.draw(arrowright);
			window.draw(playerselect);
			window.draw(corsor);

			window.display();
		}

		if (screen == 2) {
			window.clear();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				screen = 1;
			}
			window.draw(menu3);
			window.display();
		}
		if (screen == 3) {
			window.clear();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				screen = 1;
			}
			window.draw(menu3);
			window.display();
		}
		if (screen == 4) {
			window.clear();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				screen = 1;
			}
			window.draw(menu4);
			window.display();
		}
		if (screen == 5) {
			window.clear();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				screen = 1;
			}
			window.draw(menu5);
			window.display();
		}
		if(screen ==  6){
			if (newgame == true) {
				ispause = false;
				Swoosh.play();
				Song.stop();
				Song.play();
				level = 0;
				randommap();
				newgame = false;
				isdraw = false;
				player.setPosition(50.0f + shiftx, 50.0f + shifty);
				herodamage = 1;
				herohp = 3;
				sheildnum = 0;
				coin = 0;
			}
		Song.setVolume(VOL);
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
				wall.setPosition(50 * row_count + shiftx, (row * 50) + shifty);
				wall.setTexture(&Texture);
				wall.setTextureRect(sf::IntRect(x_size * 23.00000, y_size * 3.00000, x_size, y_size));
				Wall.push_back(wall);
			}
			row_count += 1;
		}
		if(ispause != true){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			Step.play();
			player.move(-50.f, 0.f);
			hand_hero.erase(hand_hero.begin(), hand_hero.end());
			hand_enemy.erase(hand_enemy.begin(), hand_enemy.end());
			walk = 1;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			}
			//printf("position x = %d position y = %d",player_posx,player_posy);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			Step.play();
			player.move(50.f, 0.0f);
			hand_hero.erase(hand_hero.begin(), hand_hero.end());
			hand_enemy.erase(hand_enemy.begin(), hand_enemy.end());
			walk = 2;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			}
			//printf("position x = %d position y = %d", player_posx, player_posy);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			Step.play();
			player.move(0.0f, -50.f);
			hand_hero.erase(hand_hero.begin(), hand_hero.end());
			hand_enemy.erase(hand_enemy.begin(), hand_enemy.end());

			walk = 3;

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			}
			//printf("position x = %d position y = %d", player_posx, player_posy);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			Step.play();
			player.move(0.0f, 50.f);
			hand_hero.erase(hand_hero.begin(), hand_hero.end());
			hand_enemy.erase(hand_enemy.begin(), hand_enemy.end());
			window.clear();
			walk = 4;
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			}
			//printf("position x = %d position y = %d", player_posx, player_posy);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
			player.setPosition(50.0f + shiftx, 50.0f + shifty);
			isdraw = false;
			randommap();
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			}
			//printf("position x = %d position y = %d", player_posx, player_posy);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
			herodamage++;

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
			}
			//printf("position x = %d position y = %d", player_posx, player_posy);
		}
		else if (player.getGlobalBounds().intersects(Door.getGlobalBounds()) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
			Stairs.play();
			player.setPosition(50.0f + shiftx, 50.0f + shifty);
			isdraw = false;
			randommap();
			//randomenemy/////
		}
		else if (herohp <= 0) {
			bool isDraw = false;
			while (herohp <= 0){
				if (isDraw == false) {
					paper.setPosition(240.0f, 100.0f);
					player_dead.setPosition(454.0f, 275.0f);
					window.draw(paper);
					window.draw(player_dead);
					window.display();
					isDraw = true;
				}
				hand_hero.erase(hand_hero.begin(), hand_hero.end());
				hand_enemy.erase(hand_enemy.begin(), hand_enemy.end());
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
					herohp = 3;
					screen = 1;
				}
			}
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			}
			ispause = true;
		}
		}

		for (int i = 0; i < healposion.size(); i++) {
			if (player.getGlobalBounds().intersects(healposion[i].getGlobalBounds())) {
				Heal.play();
				herohp = 3;
				healposion.erase(healposion.begin() + i);
			}
		}

		for (int i = 0; i < Coinitem.size(); i++) {
			if (player.getGlobalBounds().intersects(Coinitem[i].getGlobalBounds())) {
				Coin.play();
				coin += 1;
				Coinitem.erase(Coinitem.begin() + i);
			}
		}

		for (int i = 0; i < damageitem.size(); i++) {
			Attack.play();
			if (player.getGlobalBounds().intersects(damageitem[i].getGlobalBounds())) {
				Equip.play();
				herodamage += 1;
				damageitem.erase(damageitem.begin() + i);
			}
		}

		for (int i = 0; i < shielditem.size(); i++) {
			if (player.getGlobalBounds().intersects(shielditem[i].getGlobalBounds())) {
				Shield.play();
				if (sheildnum <= 5) {
					sheildnum++;
				}
				
				shielditem.erase(shielditem.begin() + i);
			}
		}


		for (int i = 0; i < Enemyvec.size(); i++) {
			if (player.getGlobalBounds().intersects(Enemyvec[i].Enemy.getGlobalBounds()) && (Enemyvec[i].GetHp()) > 0) {
				Swoosh.play();
				if (walk == 1) {
					player.move(50.f, 0.f);
				}
				else if (walk == 2) {
					player.move(-50.f, 0.0f);
				}
				else if (walk == 3) {
					player.move(0.0f, 50.f);
				}
				else if (walk == 4) {
					player.move(0.0f, -50.f);
				}
				fight = true;
				enemynum = i;
			}
		}

		for (int i = 0; i < Wall.size(); i++) {
			if (player.getGlobalBounds().intersects(Wall[i].getGlobalBounds())) {
				if (walk == 1) {
					player.move(50.f, 0.f);
				}
				else if (walk == 2) {
					player.move(-50.f, 0.0f);
				}
				else if (walk == 3) {
					player.move(0.0f, 50.f);
				}
				else if (walk == 4) {
					player.move(0.0f, -50.f);
				}
			}
		}

		for (int i = 0; i < Wall.size(); i++) {
			window.draw(Wall[i]);
		}

		bool tub = false;
		if (isdraw == false) {
			window.display();
			int rangen = randoM(1, 1 + (level / 2));
			for (int i = 0; i < rangen; i++){
				while (1){
					int ranx = randoM(1, 9);
					int rany = randoM(1, 9);
					int ranEn = randoM(1, 35);
					int ranblood = randoM(1, 1 + (level/2));
					Enemyvec.push_back(enemy(&Texture, ranEn, ranblood, 50 * ranx + shiftx, 50 * rany + shifty));
					tub = false;
					for (int j = 0; j < Wall.size(); j++) {
						if (Enemyvec.back().Enemy.getGlobalBounds().intersects(Wall[j].getGlobalBounds())) {
							tub = true;
						}
					}
					for (int j = 0; j < (Enemyvec.size()-1); j++) {
						if (Enemyvec.back().Enemy.getGlobalBounds().intersects(Enemyvec[j].Enemy.getGlobalBounds())) {
							tub = true;
						}
					}
					if (tub == false) {
						printf("*");
						break;
					}
					else {
						Enemyvec.pop_back();
					}
				}
			}
			isdraw = true;
		}
		
		for (int i = 0; i < Enemyvec.size(); i++) {
			for (int j = 0; j < Wall.size(); j++) {
				if (Enemyvec[i].Enemy.getGlobalBounds().intersects(Wall[j].getGlobalBounds())) {
					Enemyvec.erase(Enemyvec.begin() + i);
					int ranx = randoM(1, 9);
					int rany = randoM(1, 9);
					int ranEn = randoM(1, 3);
					int ranblood = randoM(1, level);
					Enemyvec.push_back(enemy(&Texture, ranEn, ranblood, 50 * ranx + shiftx, 50 * rany + shifty));
				}
				if (Enemyvec[i].Enemy.getGlobalBounds().intersects(Door.getGlobalBounds())) {
					Enemyvec.erase(Enemyvec.begin() + i);
					int ranx = randoM(1, 9);
					int rany = randoM(1, 9);
					int ranEn = randoM(1, 3);
					int ranblood = randoM(1, level);
					Enemyvec.push_back(enemy(&Texture, ranEn, ranblood, 50 * ranx + shiftx, 50 * rany + shifty));
				}
				if (Enemyvec[i].Enemy.getGlobalBounds().intersects(player.getGlobalBounds())) {
					Enemyvec.erase(Enemyvec.begin() + i);
					int ranx = randoM(1, 9);
					int rany = randoM(1, 9);
					int ranEn = randoM(1, 3);
					int ranblood = randoM(1, level);
					Enemyvec.push_back(enemy(&Texture, ranEn, ranblood, 50 * ranx + shiftx, 50 * rany + shifty));
				}
			}
		}

		for (int i = 0; i < Enemyvec.size(); i++) {
			if ((Enemyvec[i].GetHp()) <= 0) {
				int x;
				x = randoM(1, 100);
				if (x > 80 && x <= 100) {
					item.setOrigin(0.f, 0.f);//healposion
					item.setPosition(Enemyvec[i].Enemy.getPosition().x, Enemyvec[i].Enemy.getPosition().y);
					item.setTexture(&Texture);
					item.setFillColor(sf::Color::Red);
					item.setTextureRect(sf::IntRect(x_size * 18.00000, y_size * 25.00000, x_size, y_size));
					healposion.push_back(item);
				}
				else if (x > 40 && x <= 80) {
					item.setOrigin(0.f, 0.f);// coin
					item.setPosition(Enemyvec[i].Enemy.getPosition().x, Enemyvec[i].Enemy.getPosition().y);
					item.setTexture(&Texture);
					item.setFillColor(sf::Color::Yellow );
					item.setTextureRect(sf::IntRect(x_size * 9.00000, y_size * 26.00000, x_size, y_size));
					Coinitem.push_back(item);
				}
				else if (x > 20 && x <= 40) {
					item.setOrigin(0.f, 0.f);//damgeitem
					item.setFillColor(sf::Color::Blue);
					item.setPosition(Enemyvec[i].Enemy.getPosition().x, Enemyvec[i].Enemy.getPosition().y);
					item.setTexture(&Texture);
					item.setTextureRect(sf::IntRect(x_size * 0.00000, y_size * 31.00000, x_size, y_size));
					damageitem.push_back(item);
				}
				else if (x > 0 && x <= 20) {
					item.setOrigin(0.f, 0.f);// shield
					item.setFillColor(sf::Color::White);
					item.setPosition(Enemyvec[i].Enemy.getPosition().x, Enemyvec[i].Enemy.getPosition().y);
					item.setTexture(&Texture);
					item.setTextureRect(sf::IntRect(x_size * 5.00000, y_size * 26.00000, x_size, y_size));
					shielditem.push_back(item);
				}
				Enemyvec.erase(Enemyvec.begin() + i);
			}
		}
		for (int i = 0; i < Enemyvec.size(); i++) {
			Enemyvec[i].draw(window);
		}
		for (int i = 0; i < healposion.size(); i++) {
			window.draw(healposion[i]);
		}

		for (int i = 0; i < Coinitem.size(); i++) {
			window.draw(Coinitem[i]);
		}

		for (int i = 0; i < damageitem.size(); i++) {
			window.draw(damageitem[i]);
		}
		for (int i = 0; i < shielditem.size(); i++) {
			window.draw(shielditem[i]);
		}
		
		/// Blood
		for (int i = 0; i < Enemyvec.size(); i++) {
			if ((Enemyvec[i].GetHp()) < Enemyvec[i].GetmaxHp() && Enemyvec[i].GetHp() > 0) {
				sf::RectangleShape bloodmax(sf::Vector2f(50.0f, 10.0f));
				bloodmax.setOrigin(0.f, 0.f);
				bloodmax.setPosition(Enemyvec[i].Enemy.getPosition().x, Enemyvec[i].Enemy.getPosition().y - 5);
				window.draw(bloodmax);

				sf::RectangleShape blood(sf::Vector2f(42 * (Enemyvec[i].GetHp() / Enemyvec[i].GetmaxHp()), 6.0f));
				blood.setFillColor(sf::Color::Red);
				blood.setPosition(Enemyvec[i].Enemy.getPosition().x + 4, Enemyvec[i].Enemy.getPosition().y - 3);
				blood.setOrigin(0.f, 0.f);
				window.draw(blood);
			}
		}
		window.draw(Door);
		window.draw(player);

		/// UI //////////////////////////////////////////////////////////////	
		sf::RectangleShape UI(sf::Vector2f(75.0f, 75.0f));
		UI.setOrigin(0.f, 0.f);
		UI.setPosition(0, shifty);
		UI.setTexture(&Texture);
		UI.setTextureRect(sf::IntRect(x_size * 26.0000000, y_size * 22.0000000, x_size, y_size));
		window.draw(UI);

		sf::RectangleShape X(sf::Vector2f(45.0f, 45.0f));
		X.setOrigin(0.f, 0.f);
		X.setPosition(65.f, shifty + 19);
		X.setTexture(&Texture);
		X.setTextureRect(sf::IntRect(x_size * 29.0000000, y_size * 31.0000000, x_size, y_size));
		window.draw(X);


		sf::RectangleShape NUM(sf::Vector2f(70.0f, 70.0f));
		NUM.setOrigin(0.f, 0.f);
		NUM.setPosition(90.f, shifty + 3);
		NUM.setTexture(&Texture);
		NUM.setTextureRect(sf::IntRect(x_size * (19.0000000 + herohp), y_size * 29.0000000, x_size, y_size));
		window.draw(NUM);




		UI.setOrigin(0.f, 0.f);
		UI.setPosition(0 + 2.5, shifty + 75);
		UI.setTexture(&Texture);
		UI.setTextureRect(sf::IntRect(x_size * 5.0000000, y_size * 26.0000000, x_size, y_size));
		window.draw(UI);

		X.setOrigin(0.f, 0.f);
		X.setPosition(65.f, shifty + 19 + 75);
		X.setTexture(&Texture);
		X.setTextureRect(sf::IntRect(x_size * 29.0000000, y_size * 31.0000000, x_size, y_size));
		window.draw(X);

		NUM.setOrigin(0.f, 0.f);
		NUM.setPosition(90.f, shifty + 78);
		NUM.setTexture(&Texture);
		NUM.setTextureRect(sf::IntRect(x_size * (19.0000000 + sheildnum), y_size * 29.0000000, x_size, y_size));
		window.draw(NUM);



		///level//////////////////////////////////////////////
		sf::RectangleShape text(sf::Vector2f(100.0f, 100.0f));
		text.setOrigin(0.f, 0.f);
		text.setPosition(250, 0);
		text.setTexture(&Texture);
		text.setTextureRect(sf::IntRect(x_size * 30.0000000, y_size * 30.0000000, x_size, y_size));
		window.draw(text);

		text.setOrigin(0.f, 0.f);
		text.setPosition(300, 0);
		text.setTexture(&Texture);
		text.setTextureRect(sf::IntRect(x_size * 23.0000000, y_size * 30.0000000, x_size, y_size));
		window.draw(text);

		text.setOrigin(0.f, 0.f);
		text.setPosition(350, 0);
		text.setTexture(&Texture);
		text.setTextureRect(sf::IntRect(x_size * 27.0000000, y_size * 31.0000000, x_size, y_size));
		window.draw(text);

		text.setOrigin(0.f, 0.f);
		text.setPosition(400, 0);
		text.setTexture(&Texture);
		text.setTextureRect(sf::IntRect(x_size * 23.0000000, y_size * 30.0000000, x_size, y_size));
		window.draw(text);

		text.setOrigin(0.f, 0.f);
		text.setPosition(450, 0);
		text.setTexture(&Texture);
		text.setTextureRect(sf::IntRect(x_size * 30.0000000, y_size * 30.0000000, x_size, y_size));
		window.draw(text);


		sf::RectangleShape textNUM(sf::Vector2f(100.0f, 100.0f));
		if ((level / 10) > 0){
			textNUM.setOrigin(0.f, 0.f);
			textNUM.setPosition(550, 0);
			textNUM.setTexture(&Texture);
			textNUM.setTextureRect(sf::IntRect(x_size* (19.0000000 + (level / 10)), y_size * 29.0000000, x_size, y_size));
			window.draw(textNUM);
		}

		textNUM.setOrigin(0.f, 0.f);
		textNUM.setPosition(600, 0);
		textNUM.setTexture(&Texture);
		textNUM.setTextureRect(sf::IntRect(x_size* (19.0000000 + (level % 10)), y_size * 29.0000000, x_size, y_size));
		window.draw(textNUM);

		
///level//////////////////////////////////////////////
		UI.setOrigin(0.f, 0.f);
		UI.setPosition(865, shifty);
		UI.setTexture(&Texture);
		UI.setFillColor(sf::Color::Blue);
		UI.setTextureRect(sf::IntRect(x_size * 4.0000000, y_size * 30.0000000, x_size, y_size));
		window.draw(UI);

		if ((herodamage / 10) > 0) {
			NUM.setOrigin(0.f, 0.f);
			NUM.setPosition(760, shifty + 5);
			NUM.setTexture(&Texture);
			NUM.setTextureRect(sf::IntRect(x_size * (19.0000000 + (herodamage / 10)), y_size * 29.0000000, x_size, y_size));
			window.draw(NUM);
		}

		NUM.setOrigin(0.f, 0.f);
		NUM.setPosition(800, shifty + 5);
		NUM.setTexture(&Texture);
		NUM.setTextureRect(sf::IntRect(x_size * (19.0000000 + (herodamage % 10)), y_size * 29.0000000, x_size, y_size));
		window.draw(NUM);



		UI.setOrigin(0.f, 0.f);
		UI.setPosition(865, shifty + 75);
		UI.setTexture(&Texture);
		UI.setFillColor(sf::Color::Yellow);
		UI.setTextureRect(sf::IntRect(x_size * 9.0000000, y_size * 26.0000000, x_size, y_size));
		window.draw(UI);


		if ((coin / 10) > 0) {
			NUM.setOrigin(0.f, 0.f);
			NUM.setPosition(760, shifty + 80);
			NUM.setTexture(&Texture);
			NUM.setTextureRect(sf::IntRect(x_size * (19.0000000 + (coin / 10)), y_size * 29.0000000, x_size, y_size));
			window.draw(NUM);
		}

		NUM.setOrigin(0.f, 0.f);
		NUM.setPosition(800, shifty + 80);
		NUM.setTexture(&Texture);
		NUM.setTextureRect(sf::IntRect(x_size * (19.0000000 + (coin % 10)), y_size * 29.0000000, x_size, y_size));
		window.draw(NUM);


		/// UI //////////////////////////////////////////////////////////////
		if (fight == true) {
			hand_hero.erase(hand_hero.begin(), hand_hero.end());
			hand_enemy.erase(hand_enemy.begin(), hand_enemy.end());
			while (not hand_hero.empty()) hand_hero.pop_back();
			while (not hand_enemy.empty()) hand_enemy.pop_back();
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
			for (int i = 0; i < hand_hero.size(); i++)
			{
				Card[hand_hero[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y + 50);
				window.draw(Card[hand_hero[i] - 1]);
			}
			for (int i = 0; i < hand_hero.size(); i++) {
				printf(" %d", hand_hero[i]);
			}
			for (int i = 0; i < hand_enemy.size(); i++)
			{
				Card[hand_enemy[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y - 25);
				window.draw(Card[hand_enemy[i] - 1]);
			}
			//printf("1");
			window.display();
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
						Attacked.play();
						herogetdamage();
						for (int i = 0; i < hand_hero.size(); i++)
						{
							Card[hand_hero[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y + 50);
							window.draw(Card[hand_hero[i] - 1]);
						}
						for (int i = 0; i < hand_enemy.size(); i++)
						{
							Card[hand_enemy[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y - 25);
							window.draw(Card[hand_enemy[i] - 1]);

						}
						cl.restart();
						while (true) {
							Time = cl.getElapsedTime().asSeconds();
							//cout << "kuy" << endl;
							if (Time <= 0.5) {
								player.setFillColor(sf::Color::Red);
								window.draw(player);
								//cout << "itai" << endl;
							}
							else {
								player.setFillColor(sf::Color::White);
								window.draw(player);
								cout << "ahhhhh" << endl;
								break;
							}
							window.display();

						}
						break;
					}
					hand_enemy.push_back(Deck.back());
					enemy_score += card_score(Deck.back());
					for (int i = 0; i < hand_hero.size(); i++)
					{
						Card[hand_hero[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y + 50);
						window.draw(Card[hand_hero[i] - 1]);
					}
					for (int i = 0; i < hand_enemy.size(); i++)
					{
						Card[hand_enemy[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y - 25);
						window.draw(Card[hand_enemy[i] - 1]);

					}
					//printf("4");
					window.display();
					Deck.pop_back();
					if (too_more(enemy_score) == 1) {
						printf_s("\nhero is %d", hero_score);
						printf_s("\nenemy is %d\n", enemy_score);
						printf("hero is winner  ^^ \n");
						Attack.play();
						Enemyvec[enemynum].takedamage(herodamage);
						for (int i = 0; i < hand_hero.size(); i++)
						{
							Card[hand_hero[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y + 50);
							window.draw(Card[hand_hero[i] - 1]);
						}
						for (int i = 0; i < hand_enemy.size(); i++)
						{
							Card[hand_enemy[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y - 25);
							window.draw(Card[hand_enemy[i] - 1]);

						}
						//printf("5");
						window.display();
						cl.restart();
						while (true) {
							Time = cl.getElapsedTime().asSeconds();
							//cout << "kuy" << endl;
							if (Time <= 0.5) {
								Enemyvec[enemynum].Enemy.setFillColor(sf::Color::Red);
								Enemyvec[enemynum].draw(window);
								//cout << "itai" << endl;
							}
							else {
								Enemyvec[enemynum].Enemy.setFillColor(sf::Color::White);
								Enemyvec[enemynum].draw(window);
								cout << "ahhhhh" << endl;
								break;
							}
							window.display();
						}
						//printf("6");
						break;
					}
					printf("\nhand hero\n");
					window.display();
					printf("hero score");
					printf("%d", hero_score);
					for (int i = 0; i < hand_hero.size(); i++)
					{
						Card[hand_hero[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y + 50);
						window.draw(Card[hand_hero[i] - 1]);
					}
					for (int i = 0; i < hand_enemy.size(); i++)
					{
						Card[hand_enemy[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y - 25);
						window.draw(Card[hand_enemy[i] - 1]);

					}
					//printf("7");
					window.display();
					while (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {}
				}
				////////////////////////////////////////////////////
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
					for (int i = 0; i < hand_hero.size(); i++)
					{
						Card[hand_hero[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y + 50);
						window.draw(Card[hand_hero[i] - 1]);
					}
					for (int i = 0; i < hand_enemy.size(); i++)
					{
						Card[hand_enemy[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y - 25);
						window.draw(Card[hand_enemy[i] - 1]);

					}
					window.display();
					fight = false;
					printf_s("\nhero is %d", hero_score);
					printf_s("\nenemy is %d\n", enemy_score);
					if (hero_score == enemy_score) {
						printf("draw  ;-; \n");
						Swoosh.play();
					}
					if (hero_score > enemy_score) {
						printf("hero is winner  ^^ \n");\
						Attack.play();
						cl.restart();
						while (true) {
							Time = cl.getElapsedTime().asSeconds();
							//cout << "kuy" << endl;
							if (Time <= 0.5) {
								Enemyvec[enemynum].Enemy.setFillColor(sf::Color::Red);
								Enemyvec[enemynum].draw(window);
								//cout << "itai" << endl;
							}
							else {
								Enemyvec[enemynum].Enemy.setFillColor(sf::Color::White);
								Enemyvec[enemynum].draw(window);
								cout << "ahhhhh" << endl;
								break;
							}
							window.display();

						}
						Enemyvec[enemynum].takedamage(herodamage);
					}
					if (hero_score < enemy_score) {
						printf("hero is lose  TT \n");
						Attacked.play();
						herogetdamage();
						cl.restart();
						while (true) {
							Time = cl.getElapsedTime().asSeconds();
							//cout << "kuy" << endl;
							if (Time <= 0.5) {
								player.setFillColor(sf::Color::Red);
								window.draw(player);
								//cout << "itai" << endl;
							}
							else {
								player.setFillColor(sf::Color::White);
								window.draw(player);
								cout << "ahhhhh" << endl;
								break;
							}
							window.display();

						}
					}
					break;
				}
			}
			clear_card();
			enemy_score = 0;
			hero_score = 0;
			fight = false;
		}
		for (int i = 0; i < hand_hero.size(); i++)
		{
			Card[hand_hero[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y + 50);
			window.draw(Card[hand_hero[i] - 1]);
		}
		for (int i = 0; i < hand_enemy.size(); i++)
		{
			Card[hand_enemy[i] - 1].setPosition((player.getPosition().x + 25 * i) - 25, player.getPosition().y - 25);
			window.draw(Card[hand_enemy[i] - 1]);
		}
		/*
		for (int i = 0; i < 52; i++)
		{
			Card[i].setPosition(((player_posx * 50) + 25 * i) - 25, (player_posy * 50) - 25);
			window.draw(Card[i]);
		}
		*/
		//window.draw(playercard);
		if (ispause == true) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			corsor.setPosition((float)mousePos.x - 300, (float)mousePos.y - 300);
			pause_menu.setFillColor(sf::Color(255, 255, 255, 255));
			pause_volume.setFillColor(sf::Color(255, 255, 255, 255));
			pause_suicide.setFillColor(sf::Color(255, 255, 255, 255));
			pause_play.setFillColor(sf::Color(255, 255, 255, 255));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				}
				ispause = false;
			}
			
			if(corsor.getGlobalBounds().intersects(pause_menu.getGlobalBounds())){
				pause_menu.setFillColor(sf::Color(255, 255, 255, 128));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					}
					screen = 1;
				}
			}
			else if (corsor.getGlobalBounds().intersects(pause_volume.getGlobalBounds())) {
				pause_volume.setFillColor(sf::Color(255, 255, 255, 128));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					}
					if (VOL == 50) {
						VOL = 0;
					}
					else {
						VOL = 50;
					}
				}
			}

			else if (corsor.getGlobalBounds().intersects(pause_suicide.getGlobalBounds())) {
				pause_suicide.setFillColor(sf::Color(255, 255, 255, 128));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					}
					herohp = 0;
					ispause = false;
				}
			}

			else if (corsor.getGlobalBounds().intersects(pause_play.getGlobalBounds())) {
				pause_play.setFillColor(sf::Color(255, 255, 255, 128));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					}
					ispause = false;
				}
			}

			if (VOL == 50) {
				pause_volume.setTexture(&pause_volumemax_tex);;
			}
			else {
				pause_volume.setTexture(&pause_volumelow_tex);;
			}
			window.draw(pause);
			window.draw(pause_menu);
			window.draw(pause_volume);
			window.draw(pause_suicide);
			window.draw(pause_play);
			window.draw(corsor);
		}
		window.setView(view);
		window.display();
		}
	}
	return 0;
}