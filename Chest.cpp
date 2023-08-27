#include "Chest.h"
#include <iostream>

Chest::Chest(const Chest& inna) : Item()
{
	content = new ChestWindow(inna.capacity);
    capacity = inna.capacity;
	isOpen = inna.isOpen;
}

Chest::Chest(chest_v type) : Item(vault.get(type)) {
}

Chest::Chest( sf::Vector2f coordinates, chest_v chest_v, bool big, Item* newContent ) :
	Item(vault.get(chest_v), coordinates), isOpen(false), content(new ChestWindow(capacity, newContent)), capacity(big == false ? 4 : 9)
{
}

Chest::~Chest()
{
	if (content != nullptr)
		delete content;
}

Chest* Chest::getChest ( )
{
	return this;
}

Item* Chest::takeOut(sf::Vector2f mouseCoordinates)
{
	return content->takeOut(mouseCoordinates);
}

void Chest::store(const Item& item)
{
	if ( content != nullptr )
		content = new ChestWindow();

	content->store(item);
}

void Chest::showWindow (sf::RenderWindow& okno)
{
	content->pokazWnetrze(okno);
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
    return content->czyMysz(mouseCoordinates);
}
