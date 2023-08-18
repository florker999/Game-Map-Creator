#pragma once
#include "Placeable.h"
#include "Tile.h"
#include "Item.h"

class Square
{
private:
	Tile* mainTile;
	Item* item;
	Item* otherItems;

	// nullptr by default | 0 - blockade | 1 - access
	bool* additionalAccess;
	int otherItemsCounter;

public:
	Square ( );
	Square ( Tile* targetTile, Item* targetItem = nullptr );

	void drawOn ( sf::RenderWindow& window );
	void setPositon ( sf::Vector2f position );
	void operator<< ( Tile* target );
	void operator<< ( Item* target );
};

