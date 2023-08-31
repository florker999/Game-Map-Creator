#pragma once
#include "Tile.h"
#include "Variants.h"
#include "global.h"
class Wall :
    public Tile
{
private:
    wall_v type;

public:
    Wall ( wall_v type, sf::Vector2f position = sf::Vector2f{ 39, 39 } );

    void putInto ( Chest* container ) {};


    Placeable* createCopy ( ) override;
};

