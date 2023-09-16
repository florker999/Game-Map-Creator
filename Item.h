#ifndef ITEM_H
#define ITEM_H

#include "SFML/Graphics.hpp"
#include "Variants.h"
#include "Placeable.h"
#include <iostream>

class Chest;

class Item:
    public Placeable
{
private:

public:

	Item(const Item& rz) = default;
	Item(Item&& rz) = default;
    Item ( sf::Texture& texture, sf::Vector2f coordinates = sf::Vector2f ( 0, 0 ) );
    Item* createCopy ( );
    
    void putInto ( Chest* container, sf::Vector2f coord );

    virtual action_v use ( ) { return action_v::nothing; };
};

#endif
