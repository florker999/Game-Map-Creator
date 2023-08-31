#pragma once
#include "Floor.h"
#include "Variants.h"

class Blockade :
    public Placeable
{
private:
    bool blockability;

public:
    Blockade ( add_v type, sf::Vector2f position = sf::Vector2f ( 0, 0 ) );
    bool isBlocking ( );
    void putInto ( Chest* container ) {};

    Placeable* createCopy ( ) override;
};

