#include "Wall.h"

Wall::Wall ( wall_v type, sf::Vector2f position ) : Tile ( vault.get ( type ), position ), type ( type )
{
}

Placeable* Wall::createCopy ( )
{
	return new Wall ( *this );
}
