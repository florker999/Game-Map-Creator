#include "Item.h"
#include "global.h"
#include "Chest.h"

Item::Item( sf::Texture& texture, sf::Vector2f coordinates ) : Placeable( texture, coordinates ) {
}

Item* Item::createCopy()
{
    return new Item(*this);
}

bool Item::operator==( const Item& compareItem )
{
    return false;
}
