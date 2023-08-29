#include "SFML/Graphics.hpp"
#include "Square.h"
#include "Item.h"
#include "Tile.h"
#include "global.h"

sf::RectangleShape Square::accessEntity{ sf::Vector2f ( 39, 39 ) };

Square::Square ( ) : item ( nullptr ), otherItems ( nullptr ), otherItemsCounter ( 0 ), additionalAccess ( nullptr )
{
	mainTile = new Floor ( floor_v::empty );
}

Square::Square ( Tile* targetTile, Item* targetItem )
{
	mainTile = new Floor ( *dynamic_cast< Floor* >( targetTile ) );
	item = targetItem;
	otherItems = nullptr;
	otherItemsCounter = 0;
	additionalAccess = nullptr;
}

sf::Vector2f Square::getPosition ( )
{
	return mainTile->getPosition();
}

action_v Square::useItem ( )
{
	if ( item != nullptr ) return item->use ( );
	return action_v::nothing;
}

Item* Square::getItem ( )
{
	return item;
}

bool Square::contains ( sf::Vector2f point )
{
	return mainTile->contains ( point );
}

bool Square::getAddAccess ( )
{
	return additionalAccess;
}

bool Square::hasItem() const {
    return item != nullptr;
}

void Square::reset ( )
{
	sf::Vector2f oldPos = mainTile->getPosition ( );
	if ( mainTile != nullptr )
	{
		delete mainTile;
		mainTile = new Floor ( floor_v::empty, oldPos );
	}
	if ( item != nullptr )
	{
		delete item;
		item = nullptr;
	}
}

void Square::setAddAccess ( bool access )
{
	if ( additionalAccess != nullptr ) delete additionalAccess;
	additionalAccess = new bool ( access );
}

void Square::drawOn ( sf::RenderWindow& window )
{
	mainTile->drawOn ( window );
    if (item != nullptr ) item->drawOn(window);
	if ( additionalAccess != nullptr ) {
		if ( *additionalAccess == true ) accessEntity.setTexture ( &vault.get ( add_v::access ) );
		else accessEntity.setTexture ( &vault.get ( add_v::blockade ) );
		accessEntity.setPosition ( mainTile->getPosition ( ) );
		window.draw ( accessEntity );
	}
}

void Square::setPositon ( sf::Vector2f position )
{
	mainTile->setPosition ( position );
}

void Square::operator<<( Tile* target )
{
	if ( mainTile != nullptr )
	{
		delete mainTile;
	}
	if ( additionalAccess != nullptr )
	{
		delete additionalAccess;
		additionalAccess = nullptr;
	}
	mainTile = new Floor ( *dynamic_cast< Floor* >( target ) );
}

void Square::operator<<( Item* target )
{
	if ( item != nullptr ) 
	{
		delete item;
	}
	if ( additionalAccess != nullptr )
	{
		delete additionalAccess;
		additionalAccess = nullptr;
	}
	item = target;
}
