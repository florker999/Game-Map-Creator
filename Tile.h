#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"
#include "Variants.h"
#include "Vault.h"
#include "Placeable.h"

class Tile:
	public Placeable
{
private:

public:
	Tile ( );
	Tile ( sf::Texture& texture, sf::Vector2f position );

	void resetTexture();
	void init( floor_v type, sf::Vector2f position );
};

#endif
