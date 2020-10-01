#include <SFML/Graphics.hpp>
#include <iostream>

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