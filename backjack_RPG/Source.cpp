#include <SFML/Graphics.hpp>
#include <iostream>


int main() {

	sf::RenderWindow window(sf::VideoMode(500, 500), "test", sf::Style::Close | sf::Style::Resize);
	sf::Texture Texture;
	Texture.loadFromFile("new2.png");
	sf::Vector2u textureSize = Texture.getSize();
	float x_size = textureSize.x / 32.000000;
	float y_size = textureSize.y / 32.000000;
	
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
	player.setTextureRect(sf::IntRect(x_size * 31, y_size * 0, x_size, y_size));
	// position
	int player_posx = 1;
	int player_posy = 1;


	//enemy
	sf::RectangleShape enemy(sf::Vector2f(50.0f, 50.0f));
	enemy.setOrigin(0.f, 0.f);
	enemy.setPosition(250.0f, 300.0f);
	enemy.setTexture(&Texture);
	enemy.setTextureRect(sf::IntRect(x_size * 28, y_size * 5, x_size, y_size));
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
		if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
			printf("*");
		}
		/*
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x, (float)mousePos.y);
		}
		*/
		window.clear();
		for (int i = 0; i < wallx.size(); i++)
		{
			window.draw(wallx[i]);
		}
		
		for (int i = 0; i < wally.size(); i++)
		{
			window.draw(wally[i]);
		}
		window.draw(enemy);
		window.draw(player);
		window.display();
	}
	return 0;
}