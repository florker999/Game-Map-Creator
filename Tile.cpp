#include "Tile.h"
#include "typy.h"
#include "global.h"

void Tile::setTexture(typ_pod t)
{
	if (static_cast<bool>(t))
	{
		entity.setTexture(&mag.zwroc_t(t));
	}
	else
		entity.setTexture(NULL);
}

inline void Tile::setTexture ( sf::Texture& t ) { entity.setTexture ( &t ); }

inline void Tile::setPosition(sf::Vector2f p) { entity.setPosition(p); }

void Tile::drawOn ( sf::RenderWindow& window )
{
	window.draw ( entity );
}

inline void Tile::resetTexture ( ) { entity.setTexture ( NULL ); }

bool Tile::contains( sf::Vector2f p )
{
	return entity.getGlobalBounds().contains(p);
}

sf::Vector2f Tile::getPosition ( ) { return entity.getPosition ( ); }

Tile::Tile()
{
	entity.setSize(sf::Vector2f(39, 39));
	entity.setOrigin ( 0, entity.getLocalBounds ( ).height );
	entity.setFillColor( sf::Color::Transparent );
}

Tile::Tile ( sf::Vector2f position ): Tile ( )
{
	setPosition (position);
}

void Tile::init ( sf::Vector2f p, typ_pod tP )
{
	entity.setTexture ( NULL );
	entity.setSize(sf::Vector2f(39, 39));
	entity.setOrigin(0, entity.getLocalBounds().height);
	setPosition (p);
}