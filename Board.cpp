#include "Board.h"

Board::Board ( int squaresNumber ) : aboveBoard ( nullptr ), belowBoard ( nullptr ), leftBoard ( nullptr ), rightBoard ( nullptr ), squaresNumber( squaresNumber )
{
	sf::Vector2f position ( 0, 39 );
	squares = new Square[ squaresNumber ];
	for ( int i = 0; i < squaresNumber; i++ )
	{
		squares[ i ].setPositon ( position );

		// iterating to next tile
		position.x += 39;
		if ( position.x > 975 ) {
			position.x = 0;
			position.y += 39;
		}
	}
}

void Board::drawOn ( sf::RenderWindow& window )
{
	for ( int i = 0; i < squaresNumber; i++ )
	{
		squares[ i ].drawOn ( window );
	}
}

Board* Board::addBoard ( int direction ) // 0 - above | 1 - right | 2 - below | 3 - left
{
	Board* newBoard = new Board ( squaresNumber );
	if ( direction == 0 ) aboveBoard = newBoard;
	else if ( direction == 1 ) rightBoard = newBoard;
	else if ( direction == 2 ) belowBoard = newBoard;
	else leftBoard = newBoard;
	return newBoard;
}

void Board::removeBoard ( )
{
}

void Board::setSquare ( int squareNumber, Tile* target )
{
	squares[ squareNumber ] << target;
}

void Board::setSquare ( int squareNumber, Item* target )
{
	squares[ squareNumber ] << target;
}