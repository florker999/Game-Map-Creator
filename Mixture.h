#pragma once

#include "Item.h"
#include "Variants.h"
#include "global.h"

class Mixture :
    public Item
{
private:
    bool health = true;

public:
    Mixture ( ) = default;
    Mixture( sf::Vector2f poz ) : Item( vault.get ( mixture_v::health ), poz ) { }

    action_v use() override { return action_v::nothing; }

    bool operator== ( const Item& compareItem ) override;

    Mixture* createCopy ( );
};

