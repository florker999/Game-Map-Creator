#include "Chest.h"
#include <iostream>

Chest::Chest ( const Chest& inna ) : Item ( ), window ( ChestWindow ( inna.capacity ) )
{
    capacity = inna.capacity;
	isOpen = inna.isOpen;
}

Chest::Chest ( chest_v type ) : Item ( vault.get ( type ) ), window ( 9 ) {
}

Chest::Chest( chest_v type, sf::Vector2f coordinates, bool big, Item* newContent ) :
	Item(vault.get(type), coordinates), isOpen(false), window(ChestWindow(capacity, newContent)), capacity(big == false ? 4 : 9)
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

void Chest::store(Item& item)
{
	window.store(item);
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

bool Chest::containsChestWindow(sf::Vector2f mouseCoordinates) {
    return window.contains(mouseCoordinates);
}
