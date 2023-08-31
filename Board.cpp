#include "Board.h"

Board::Board ( int squaresNumber ) : squaresNumber ( squaresNumber ), aboveBoard ( nullptr ), belowBoard ( nullptr ), leftBoard ( nullptr ), rightBoard ( nullptr )
{
	squares = new Square[ squaresNumber ];
	sf::Vector2f position ( 0, 39 );
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

Item* Board::getItemOnSquare ( int index )
{
	return squares[ index ].getItem ( );
}

action_v Board::useItemOnSquare ( int index )
{
	return squares[ index ].useItem ( );
}

sf::Vector2f Board::getCoordinatesOnSquare ( int index )
{
	return squares[ index ].getPosition ( );
}

int Board::findMousePos ( sf::Vector2f mouseCoordinates )
{
	for ( int i = 0; i < squaresNumber; i++ )
	{
		if ( squares[ i ].contains ( mouseCoordinates ) ) return i;
	}
	return -1;
}

bool Board::hasItemOnSquare(int index) const {
    return squares[index].hasItem();
}

bool Board::getAddAccessOnSquare ( int index )
{
	return squares[index].getAddAccess();
}

void Board::removeBoard ( )
{
}

void Board::resetSquare ( int index )
{
	squares[ index ].reset ( );
}

void Board::setAddAccessOnSquare ( int index, bool access )
{
	squares[ index ].setAddAccess ( access );
}

void Board::setSquare ( int index, Tile* target )
{
	squares[ index ] << target;
}

void Board::setSquare ( int index, Item* target )
{
	squares[ index ] << target;
}

void Board::setSquare ( int index, Placeable* target )
{
	if ( dynamic_cast< Item* >( target ) != nullptr ) {
		setSquare ( index, dynamic_cast< Item* >( target ) );
    } else if (dynamic_cast<Tile*>(target) != nullptr) {
		setSquare ( index, dynamic_cast< Tile* >( target ) );
    }
}
