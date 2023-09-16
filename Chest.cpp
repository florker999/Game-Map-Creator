#include "Chest.h"
#include <iostream>

Chest::Chest ( const Chest& inna ) : Item ( vault.get ( chest_v::wooden ), inna.getPosition ( ) ), window ( ChestWindow ( inna.capacity ) )
{
    capacity = inna.capacity;
	isOpen = inna.isOpen;
}

Chest::Chest(chest_v type) : Item(vault.get(type)), window(9), capacity(9), isOpen(false)
{
}

Chest::Chest( chest_v type, sf::Vector2f coordinates, bool big, Item* newContent ) :
	Item(vault.get(type), coordinates), isOpen(false), window(ChestWindow(capacity, newContent)), capacity(big == false ? 9 : 16)
{
}

Chest* Chest::getChest ( )
{
	return this;
}

Item* Chest::takeOut(sf::Vector2f mouseCoordinates)
{
	return window.takeOut(mouseCoordinates);
}

void Chest::store(Item& item, sf::Vector2f coord)
{
	window.store(item, coord);
}

void Chest::showWindow (sf::RenderWindow& okno)
{
	window.drawOn(okno);
}

action_v Chest::use()
{
	if (isOpen == 0)
	{
		open();
		return action_v::open_ch;
	}
	else
	{
		close();
		return action_v::close_ch;
	}
}

Chest* Chest::createCopy()
{
	return new Chest( *this );
}

bool Chest::containsChestWindow(sf::Vector2f mouseCoordinates) {
    return window.contains(mouseCoordinates);
}
