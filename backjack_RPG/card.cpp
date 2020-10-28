#include "card.h"
#include <iostream>
#include <time.h>



card::card(sf::Texture &texure)
{
	body.setTexture(&texure);
}

void card::draw(sf::RenderWindow& window){
	window.draw(body);
}
