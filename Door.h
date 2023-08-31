#pragma once
#include "Item.h"
#include "global.h"
class Door :
    public Item
{
public:
    Door ( door_v type, sf::Vector2f position = sf::Vector2f ( 0, 0 ) );

    Placeable* createCopy ( );
};

