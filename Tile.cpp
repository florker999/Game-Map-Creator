#include "Tile.h"
#include "Variants.h"
#include "global.h"

Tile::Tile() : Placeable()
{
}

Tile::Tile ( sf::Texture& texture, sf::Vector2f position ): Placeable ( texture, position )
{
}

inline void Tile::resetTexture ( ) { entity.setTexture ( NULL ); }


void Tile::init ( floor_v type, sf::Vector2f position )
{
	entity.setTexture ( NULL );
	entity.setSize(sf::Vector2f(39, 39));
	entity.setOrigin(0, entity.getLocalBounds().height);
	setPosition (position);
}
