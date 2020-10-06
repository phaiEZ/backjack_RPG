#include <SFML/Graphics.hpp>
#include <iostream>
/*
int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 900), "awesome_game", sf::Style::Close);

	////// Texture
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("new2.png"))
	{
		std::cout << "Load failed" << std::endl;
	}
	////// Sprite
	sf::Sprite shapeSprite;
	shapeSprite.setTexture(playerTexture);
	float spriteX = playerTexture.getSize().x / 32.00000;
	float spriteY = playerTexture.getSize().y / 32.00000;
	shapeSprite.setTextureRect(sf::IntRect(0, 0, spriteX, spriteY));
	sf::Vector2f spawnPoint = { 450- spriteY , 450 - spriteX  };
	shapeSprite.setPosition(spawnPoint);

	/// wallpaper
	sf::Texture wallpaper_;
	if (!playerTexture.loadFromFile("new2.png"))
	{
		std::cout << "Load failed" << std::endl;
	}
	sf::Sprite wallpaper;
	wallpaper.setTexture(wallpaper_);
	while (window.isOpen())
	{
		window.draw(shapeSprite);
		window.draw(shapeSprite);
		shapeSprite.setTextureRect(sf::IntRect(spriteX * 31.00000, spriteY * 0.00000, spriteX, spriteY));
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			shapeSprite.move(50, 0);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			shapeSprite.move(-50, 0);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			shapeSprite.move(0, 50);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			shapeSprite.move(0, -50);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		window.clear();
	}
	return 0;
}
*/

int main() {

	sf::RenderWindow window(sf::VideoMode(512, 512), "test", sf::Style::Close | sf::Style::Resize);
	sf::RectangleShape player(sf::Vector2f(50.0f, 50.0f));
	player.setOrigin(25.0f, 25.0f);
	player.setPosition(25.0f, 25.0f);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("new2.png");
	player.setTexture(&playerTexture);

	sf::Vector2u textureSize = playerTexture.getSize();
	float x = textureSize.x / 32.00000;
	float y = textureSize.y /= 32.00000;
	player.setTextureRect(sf::IntRect(x * 25, y * 0, x, y));



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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			player.move(-50.f,0.f);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			player.move(50.f, 0.0f);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			player.move(0.0f, -50.f);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			player.move(0.0f, 50.f);
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			player.setPosition((float)mousePos.x, (float)mousePos.y);
		}
		window.clear();
		window.draw(player);
		window.display();
	}
	return 0;
}