#include "Square.h"
#include "Item.h"
#include "Tile.h"

Square::Square ( ) : item ( nullptr ), otherItems ( nullptr ), otherItemsCounter ( 0 ), additionalAccess ( nullptr )
{
	mainTile = new Tile;
}

Square::Square ( Tile* targetTile, Item* targetItem )
{
	mainTile = new Tile ( *targetTile );
	item = targetItem;
	otherItems = nullptr;
	otherItemsCounter = 0;
	additionalAccess = nullptr;
}

void Square::drawOn ( sf::RenderWindow& window )
{
	window.draw ( mainTile->wygladOb );
	window.draw ( item->zwrocSpr ( ) );
}

void Square::setPositon ( sf::Vector2f position )
{
	mainTile->zmienPoz ( position );
}

void Square::operator<<( Tile* target )
{
	if ( mainTile != nullptr )
	{
		delete mainTile;
	}
	mainTile = new Tile(*target);
}

void Square::operator<<( Item* target )
{
	if ( item != nullptr ) 
	{
		delete item;
	}
	item = target->stworzWg ( );
}
