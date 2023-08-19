#pragma once
#include "SFML/Graphics.hpp"
#include "Placeable.h"
#include "Tile.h"
#include "Item.h"
#include "typy.h"
#include "global.h"

class Square
{
private:
	Tile* mainTile;
	Item* item;
	Item* otherItems;

	// nullptr by default | 0 - blockade | 1 - access
	static sf::RectangleShape accessEntity;
	bool* additionalAccess;
	int otherItemsCounter;

public:
	Square ( );
	Square ( Tile* targetTile, Item* targetItem = nullptr );

	sf::Vector2f getPosition ( );

	typ_akc useItem ( );
	Item* getItem ( );

	bool contains ( sf::Vector2f point );
	bool getAddAccess ( );

	void reset ( );
	void setAddAccess ( bool access );
	void drawOn ( sf::RenderWindow& window );
	void setPositon ( sf::Vector2f position );
	void operator<< ( Tile* target );
	void operator<< ( Item* target );
};

