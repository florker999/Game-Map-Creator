#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"
#include "typy.h"
#include "Tmagazyn.h"

class Tile
{
private:
	sf::RectangleShape entity;

public:
	Tile ( );
	Tile ( sf::Vector2f position );

	sf::Vector2f getPosition();

	void resetTexture();
	void setTexture(typ_pod t);
	void setTexture(sf::Texture& t);
	void setPosition(sf::Vector2f p);
	void drawOn ( sf::RenderWindow& window );
	void init( sf::Vector2f, typ_pod = typ_pod::pusty );

	bool contains ( sf::Vector2f p);
};

#endif