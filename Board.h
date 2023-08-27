#pragma once
#include "Tile.h"
#include "typy.h"
#include "Square.h"
#include "Item.h"

class Placeable;

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

	sf::Vector2f getCoordinatesOnSquare ( int index );

	int findMousePos ( sf::Vector2f mouseCoordinates );

    bool hasItemOnSquare (int index) const;
	bool getAddAccessOnSquare ( int index );

	void removeBoard ( );
	void resetSquare ( int index );
	void setAddAccessOnSquare ( int index, bool access );
	void drawOn ( sf::RenderWindow& window );
	void setSquare ( int index, Tile* target );
	void setSquare ( int index, Item* target );
    void setSquare ( int index, Placeable* target );
};

