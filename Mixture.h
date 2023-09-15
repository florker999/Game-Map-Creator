#pragma once

#include "Item.h"
#include "Variants.h"
#include "global.h"

class Mixture :
    public Item
{
private:

public:
    Mixture ( ) = default;
    Mixture( sf::Vector2f poz ) : Item( vault.get ( mixture_v::health ), poz ) { }

    action_v use() override { return action_v::nothing; }

    Mixture* createCopy ( );
};

