#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 900), "awesome_game", sf::Style::Close);

	////// Texture
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("achievements.png"))
	{
		std::cout << "Load failed" << std::endl;
	}

	////// Sprite
	sf::Sprite shapeSprite;
	shapeSprite.setTexture(playerTexture);
	float spriteX = playerTexture.getSize().x / 32.00000;
	float spriteY = playerTexture.getSize().y / 32.00000;
	shapeSprite.setTextureRect(sf::IntRect(0, 0, spriteX, spriteY));
	sf::Vector2f spawnPoint = { 0.f, 0.f };
	shapeSprite.setPosition(spawnPoint);

	while (window.isOpen())
	{
		window.draw(shapeSprite);
		shapeSprite.setTextureRect(sf::IntRect(spriteX * 31.00000, spriteY * 0.00000, spriteX, spriteY));
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			shapeSprite.move(.1f, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			shapeSprite.move(-.1f, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			shapeSprite.move(0.f, .1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			shapeSprite.move(0.f, -.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		window.clear();
	}
	return 0;
}