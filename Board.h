#pragma once
#include "Square.h"
#include "Item.h"
#include "Tile.h"
#include "typy.h"

class Board
{
private:

	Square* squares;

	Board* aboveBoard;
	Board* belowBoard;
	Board* leftBoard;
	Board* rightBoard;

	int squaresNumber;
public:
	Board ( int squaresNumber );

	Board* addBoard ( int direction );
	Item* getItemOnSquare ( int index );
	typ_akc useItemOnSquare ( int index );

	sf::Vector2f getCoordinatesOfSquare ( int index );

	int findMousePos ( sf::Vector2f mouseCoordinates );

	bool getAddAccessOfTile ( int index );

	void removeBoard ( );
	void resetSquare ( int index );
	void setAddAccessOnSquare ( int index, bool access );
	void drawOn ( sf::RenderWindow& window );
	void setSquare ( int index, Tile* target );
	void setSquare ( int index, Item* target );
};

