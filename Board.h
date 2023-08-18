#pragma once
#include "Square.h"
#include "Item.h"
#include "Tile.h"

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

	void drawOn ( sf::RenderWindow& window );
	void removeBoard ( );
	void setSquare ( int squareNumber, Tile* target );
	void setSquare ( int squareNumber, Item* target );
};

