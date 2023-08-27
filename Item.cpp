#include "Item.h"
#include "global.h"
#include "Chest.h"

Item::Item() : Placeable() {
}

Item::Item( sf::Texture& texture, sf::Vector2f coordinates ) : Placeable( texture, coordinates ) {
}

void Item::putInto( Chest* container ) {
    container->store( *this );
}
